#include "OutboundPacket.h"
#include "../VarInt.h"
#include "../MinecraftServer.h"

void OutboundPacket::send(const std::shared_ptr<Connection> &conn) {
    ByteBuffer in;
    write_data(in);

    uint8_t packet_id_length = VarInt::encoding_length(m_packet_id);
    uint32_t data_length = in.get_data_length();

    ByteBuffer packed;

    if (!conn->get_compress_packets()) {
        packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
        packed.write_varint(m_packet_id);
        packed.write_bytes(in.read_bytes(data_length));
    } else {
        toml::value server_config = MinecraftServer::get_server()->get_config_manager().get_server_config();
        auto compression_threshold = toml::find<uint32_t>(server_config, "compression_threshold");

        ByteBuffer tmp;
        tmp.write_varint(m_packet_id);
        tmp.write_bytes(in.read_bytes(data_length));
        uint32_t uncompressed_data_length = tmp.get_data_length();
        uint8_t uncompressed_data_length_encoding_length = VarInt::encoding_length(uncompressed_data_length);

        if (uncompressed_data_length < compression_threshold) {
            packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
            packed.write_varint(0);
            packed.write_bytes(tmp.read_bytes(uncompressed_data_length));
        } else {
            tmp.compress_buffer();
            packed.write_varint(static_cast<int32_t>(uncompressed_data_length_encoding_length + tmp.get_data_length()));
            packed.write_varint(uncompressed_data_length_encoding_length);
            packed.write_bytes(tmp.read_bytes(tmp.get_data_length()));
        }
    }

    packed.set_data(conn->encrypt_bytes(packed.get_data()));

    std::deque<uint8_t> data = packed.get_data();

    asio::async_write(
            *conn->get_socket(),
            asio::buffer(std::vector(data.begin(), data.end())),
            asio::transfer_all());
}
