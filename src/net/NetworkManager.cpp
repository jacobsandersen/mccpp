//
// Created by simple on 11/17/23.
//

#include <glog/logging.h>
#include "NetworkManager.h"
#include "../VarInt.h"

void NetworkManager::start() {
    start_accept();
    m_context.run();
}

void NetworkManager::start_accept() {
    auto conn = std::make_shared<Connection>(m_context);
    m_acceptor.async_accept(*conn->get_socket(), [this, conn](const asio::error_code &err) {
        if (!err) {
            LOG(INFO) << "Connection established from " << conn->get_socket()->remote_endpoint().address().to_string();
            std::thread([this, conn]() {
                start_read(conn);
            }).detach();

            start_accept();
        } else {
            LOG(WARNING) << "Failed to accept connection: " << err.message();
        }
    });
}

void NetworkManager::start_read(const std::shared_ptr<Connection> &conn) {
    auto buf = new asio::streambuf;

    asio::async_read(
            *conn->get_socket(),
            *buf,
            asio::transfer_at_least(1),
            [this, conn, buf](const asio::error_code &err, size_t bytes_transferred) {
                if (!err) {
                    LOG(INFO) << "Read " << bytes_transferred << " bytes from connection socket";

                    std::istream is(buf);

                    LOG(INFO) << "Copying data into a ByteBuffer";

                    ByteBuffer tmp;
                    for (int i = 0; i < bytes_transferred; i++) {
                        char raw;
                        is.read(&raw, 1);
                        tmp.write_byte(raw);
                    }

                    delete buf;

                    LOG(INFO) << "ByteBuffer created. Size = " << tmp.get_data_length() << " bytes.";

                    LOG(INFO) << "Decrypting data (if necessary)";

                    tmp.set_data(conn->decrypt_bytes(tmp.get_data()));

                    LOG(INFO) << "Appending data to connection buffer. Size before append = " << conn->get_data_buffer().get_data_length() << " bytes.";

                    conn->get_data_buffer().append(tmp);

                    LOG(INFO) << "Connection buffer appended. Size = " << conn->get_data_buffer().get_data_length() << " bytes";

                    LOG(INFO) << "Processing connection buffer...";

                    process_buffer(conn);

                    LOG(INFO) << "Stopped processing connection buffer, reading from network again";

                    start_read(conn);
                }
            });
}

void NetworkManager::process_buffer(const std::shared_ptr<Connection> &conn) {
    BufferReadContext& ctx = conn->get_read_context();
    ByteBuffer &buffer = conn->get_data_buffer();

    switch (ctx.read_state) {
        case BufferReadState::ReadPacketLength: {
            LOG(INFO) << "In ReadPacketLength state";

            if (buffer.get_data_length() == 0) {
                LOG(INFO) << "Connection buffer has no data. Going to read more.";
                return;
            }

            if (!ctx.packet_length) {
                LOG(INFO) << "Packet length was not previously read, reading...";
                ctx.packet_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            LOG(INFO) << "Read packet length " << *ctx.packet_length;

            if (buffer.get_data_length() < *ctx.packet_length) {
                LOG(INFO) << "Buffer did not contain enough data to read entire packet";
                return;
            }

            LOG(INFO) << "Main buffer still contains " << buffer.get_data_length() << " bytes.";

            if (conn->get_compress_packets()) {
                LOG(INFO) << "Packet compression is enabled. Next state -> ReadDataLength";
                ctx.read_state = BufferReadState::ReadDataLength;
            } else {
                LOG(INFO) << "Packet compression not enabled. Copying data into temporary buffer.";
                ctx.partial_buffer = std::make_unique<ByteBuffer>();
                ctx.partial_buffer->write_ubytes(buffer.read_ubytes(*ctx.packet_length));
                LOG(INFO) << "Temporary buffer created. Size = " << ctx.partial_buffer->get_data_length() << ".";
                LOG(INFO) << "Main buffer still contains " << buffer.get_data_length() << " bytes. Next state -> ReadPacketId";
                ctx.read_state = BufferReadState::ReadPacketId;
            }

            LOG(INFO) << "ReadPacketLength state finished. Recursing.";
            process_buffer(conn);
            break;
        }
        case BufferReadState::ReadDataLength: {
            LOG(INFO) << "In ReadDataLength state";

            if (!ctx.data_length) {
                LOG(INFO) << "Data length was not previously read, reading...";
                ctx.data_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            LOG(INFO) << "Read Data length " << *ctx.data_length;

            if (buffer.get_data_length() < *ctx.data_length && *ctx.data_length != 0) {
                LOG(INFO) << "Buffer did not contain enough data to read entire packet";
                return;
            }

            LOG(INFO) << "Main buffer still contains " << buffer.get_data_length() << " bytes.";

            ctx.partial_buffer = std::make_unique<ByteBuffer>();

            LOG(INFO) << "Copying real packet length (" << *ctx.packet_length - VarInt::encoding_length(*ctx.data_length) << ") bytes to temporary buffer.";
            ctx.partial_buffer->write_ubytes(buffer.read_ubytes(*ctx.packet_length - VarInt::encoding_length(*ctx.data_length)));
            LOG(INFO) << "Main buffer still contains " << buffer.get_data_length() << " bytes. Next state -> ReadPacketId";

            if (*ctx.data_length == 0) {
                LOG(INFO) << "Data length == 0: Buffer not actually compressed. Next state -> ReadPacketId";
                ctx.read_state = BufferReadState::ReadPacketId;
            } else {
                LOG(INFO) << "Data length > 0: Buffer is compressed. Next state -> DecompressData";
                ctx.read_state = BufferReadState::DecompressData;
            }

            LOG(INFO) << "Temporary buffer created. Size = " << ctx.partial_buffer->get_data_length();

            LOG(INFO) << "ReadDataLength state finished. Recursing.";
            process_buffer(conn);
            break;
        }

        case BufferReadState::DecompressData: {
            LOG(INFO) << "In DecompressData state";
            LOG(INFO) << "Temporary buffer before decompression size = " << ctx.partial_buffer->get_data_length() << " bytes";
            ctx.partial_buffer->decompress_buffer();
            LOG(INFO) << "Temporary buffer after decompression size = " << ctx.partial_buffer->get_data_length() << " bytes";
            LOG(INFO) << "Data decompressed. Next state -> ReadPacketId";
            ctx.read_state = BufferReadState::ReadPacketId;
            LOG(INFO) << "DecompressData state finished. Recursing.";
            process_buffer(conn);
            break;
        }

        case BufferReadState::ReadPacketId: {
            LOG(INFO) << "In ReadPacketId state";
            ctx.packet_id = std::make_unique<int32_t>(ctx.partial_buffer->read_varint());
            LOG(INFO) << "Read packet ID " << *ctx.packet_id << ". Next state -> HandlePacket";
            ctx.read_state = BufferReadState::HandlePacket;
            LOG(INFO) << "ReadPacketId state finished. Recursing.";
            process_buffer(conn);
            break;
        }

        case BufferReadState::HandlePacket: {
            LOG(INFO) << "In HandlePacket state";

            auto& handlers = *m_packet_handlers.find(conn->get_state())->second;
            if (!handlers.count(*ctx.packet_id)) {
                LOG(WARNING) << "Tried to handle unknown packet " << *ctx.packet_id << " in state " << static_cast<int>(conn->get_state());
            } else {
                LOG(INFO) << "Packet handler exists in this (state, packet id) combination. Forwarding to packet handler.";
                handlers.find(*ctx.packet_id)->second->handle(conn, ctx.partial_buffer);
            }

            ctx.packet_length = nullptr;
            ctx.data_length = nullptr;
            ctx.packet_id = nullptr;
            ctx.partial_buffer = nullptr;
            ctx.read_state = BufferReadState::ReadPacketLength;

            LOG(INFO) << "HandlePacket state finished. Read context reset. Next state -> ReadPacketLength. Recursing.";

            process_buffer(conn);

            break;
        }
    }
}
