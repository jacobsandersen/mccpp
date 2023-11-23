#include <glog/logging.h>
#include "NetworkManager.h"
#include "../VarInt.h"
#include "../MinecraftServer.h"

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
                    std::istream is(buf);

                    ByteBuffer tmp;
                    for (int i = 0; i < bytes_transferred; i++) {
                        char raw;
                        is.read(&raw, 1);
                        tmp.write_byte(raw);
                    }

                    delete buf;

                    tmp.set_data(conn->decrypt_bytes(tmp.get_data()));

                    conn->get_data_buffer().append(tmp);

                    process_buffer(conn);

                    start_read(conn);
                } else {
                    MinecraftServer::get_server()->remove_player(conn->get_unique_id());
                    conn->get_socket()->close();
                }
            });
}

void NetworkManager::process_buffer(const std::shared_ptr<Connection> &conn) {
    BufferReadContext& ctx = conn->get_read_context();
    ByteBuffer &buffer = conn->get_data_buffer();

    switch (ctx.read_state) {
        case BufferReadState::ReadPacketLength: {
            if (buffer.get_data_length() == 0) {
                return;
            }

            if (!ctx.packet_length) {
                ctx.packet_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            if (buffer.get_data_length() < *ctx.packet_length) {
                return;
            }

            if (conn->get_compress_packets()) {
                ctx.read_state = BufferReadState::ReadDataLength;
            } else {
                ctx.partial_buffer = std::make_unique<ByteBuffer>();
                ctx.partial_buffer->write_ubytes(buffer.read_ubytes(*ctx.packet_length));
                ctx.read_state = BufferReadState::ReadPacketId;
            }

            process_buffer(conn);
            break;
        }
        case BufferReadState::ReadDataLength: {
            if (!ctx.data_length) {
                ctx.data_length = std::make_unique<int32_t>(buffer.read_varint());
            }

            if (buffer.get_data_length() < *ctx.data_length && *ctx.data_length != 0) {
                return;
            }

            ctx.partial_buffer = std::make_unique<ByteBuffer>();
            ctx.partial_buffer->write_ubytes(buffer.read_ubytes(*ctx.packet_length - VarInt::encoding_length(*ctx.data_length)));

            if (*ctx.data_length == 0) {
                ctx.read_state = BufferReadState::ReadPacketId;
            } else {
                ctx.read_state = BufferReadState::DecompressData;
            }

            process_buffer(conn);
            break;
        }

        case BufferReadState::DecompressData: {
            ctx.partial_buffer->decompress_buffer();
            ctx.read_state = BufferReadState::ReadPacketId;
            process_buffer(conn);
            break;
        }

        case BufferReadState::ReadPacketId: {
            ctx.packet_id = std::make_unique<int32_t>(ctx.partial_buffer->read_varint());
            ctx.read_state = BufferReadState::HandlePacket;
            process_buffer(conn);
            break;
        }

        case BufferReadState::HandlePacket: {
            auto& handlers = *m_packet_handlers.find(conn->get_state())->second;
            if (!handlers.count(*ctx.packet_id)) {
                LOG(WARNING) << "Tried to handle unknown packet " << *ctx.packet_id << " in state " << static_cast<int>(conn->get_state());
            } else {
                handlers.find(*ctx.packet_id)->second->handle(conn, ctx.partial_buffer);
            }

            ctx.packet_length = nullptr;
            ctx.data_length = nullptr;
            ctx.packet_id = nullptr;
            ctx.partial_buffer = nullptr;
            ctx.read_state = BufferReadState::ReadPacketLength;

            process_buffer(conn);

            break;
        }
    }
}
