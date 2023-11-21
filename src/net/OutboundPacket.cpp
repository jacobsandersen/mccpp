#include <glog/logging.h>
#include "OutboundPacket.h"
#include "../VarInt.h"
#include "../MinecraftServer.h"

void OutboundPacket::send(const std::shared_ptr<Connection> &conn) {
    LOG(INFO) << "Sending a packet...";

    ByteBuffer in;
    write_data(in);

    uint8_t packet_id_length = VarInt::encoding_length(m_packet_id);
    uint32_t data_length = in.get_data_length();
    uint8_t data_length_length = VarInt::encoding_length(data_length);

    ByteBuffer packed;

    if (!conn->get_compress_packets()) {
        LOG(INFO) << "Packet compression is disabled. Packing standard format packet.";
        packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
        packed.write_varint(m_packet_id);
        packed.write_bytes(in.read_bytes(data_length));
    } else {
        LOG(INFO) << "Packet compression is enabled. Packing compressed format packet.";

        toml::value server_config = MinecraftServer::get_server()->get_config_manager().get_server_config();
        auto compression_threshold = toml::find<uint32_t>(server_config, "compression_threshold");

        if (data_length < compression_threshold) {
            LOG(INFO) << "Data length is less than compression threshold. Will not compress.";
            packed.write_varint(static_cast<int32_t>(VarInt::encoding_length(0) + packet_id_length + data_length));
            packed.write_varint(0);
            packed.write_varint(m_packet_id);
            packed.write_bytes(in.read_bytes(data_length));
        } else {
            LOG(INFO) << "Data length is greater than or equal to compression threshold. Will compress.";
            LOG(INFO) << "Creating temp buffer to compress";
            ByteBuffer tmp;
            tmp.write_varint(m_packet_id);
            tmp.write_bytes(in.read_bytes(data_length));
            tmp.compress_buffer();
            LOG(INFO) << "Temp buffer compressed with packet id and data inside.";

            packed.write_varint(static_cast<int32_t>(data_length_length + tmp.get_data_length()));
            packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
            packed.append(tmp);
        }
    }

    packed.set_data(conn->encrypt_bytes(packed.get_data()));

    std::deque<uint8_t> data = packed.get_data();

    asio::async_write(
            *conn->get_socket(),
            asio::buffer(std::vector(data.begin(), data.end())),
            asio::transfer_all());
}
