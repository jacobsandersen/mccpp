#include <glog/logging.h>
#include "OutboundPacket.h"
#include "../VarInt.h"
#include "../MinecraftServer.h"

void OutboundPacket::send(const std::shared_ptr<Connection>& conn)
{
    ByteBuffer in;
    write_data(conn, in);

    uint8_t packet_id_length = VarInt::encoding_length(m_packet_id);
    uint32_t data_length = in.get_data_length();
    uint8_t data_length_length = VarInt::encoding_length(data_length);

    ByteBuffer packed;

    if (!conn->get_compress_packets())
    {
        packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
        packed.write_varint(m_packet_id);
        packed.write_bytes(in.read_bytes(data_length));
    }
    else
    {
        toml::value server_config = MinecraftServer::get_server()->get_config_manager().get_server_config();
        auto compression_threshold = toml::find<uint32_t>(server_config, "compression_threshold");

        if (data_length < compression_threshold)
        {
            packed.write_varint(static_cast<int32_t>(VarInt::encoding_length(0) + packet_id_length + data_length));
            packed.write_varint(0);
            packed.write_varint(m_packet_id);
            packed.write_bytes(in.read_bytes(data_length));
        }
        else
        {
            ByteBuffer tmp;
            tmp.write_varint(m_packet_id);
            tmp.write_bytes(in.read_bytes(data_length));
            tmp.compress_buffer();

            packed.write_varint(static_cast<int32_t>(data_length_length + tmp.get_data_length()));
            packed.write_varint(static_cast<int32_t>(packet_id_length + data_length));
            packed.append(tmp);
        }
    }

    packed.set_data(conn->encrypt_bytes(packed.get_data()));

    std::deque<uint8_t> data = packed.get_data();
    const auto buffer = std::make_shared<std::vector<uint8_t>>(std::vector(data.begin(), data.end()));

    LOG(INFO) << "OutboundPacket - now calling boost::asio::async_write";
    boost::asio::async_write(
        *conn->get_socket(),
        boost::asio::buffer(*buffer),
        boost::asio::transfer_all(),
        [](const boost::system::error_code& ec, std::size_t bytes_transferred)
        {
            if (ec)
            {
                LOG(ERROR) << "OutboundPacket - boost::asio::async_write failed: " << ec.message();
            }
            else
            {
                LOG(INFO) << "OutboundPacket - bytes transferred: " << bytes_transferred;
            }
        });
}
