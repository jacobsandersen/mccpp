#include "PacketHandshakingInHandshake.h"
#include <glog/logging.h>

void
PacketHandshakingInHandshake::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer,
                                     size_t *bytes_available) {
    int32_t protocol_version = buffer->read_varint();
    LOG(INFO) << "Protocol version: " << protocol_version;

    std::string server_address = buffer->read_string();
    LOG(INFO) << "Server address: \"" << server_address << "\"";

    uint16_t server_port = buffer->read_short();
    server_port = be16toh(server_port);
    LOG(INFO) << "Server port: " << server_port;

    int32_t next_state = buffer->read_varint();
    LOG(INFO) << "Next state: " << next_state;

    LOG(INFO) << "Setting connection state to " << next_state << "...";
    conn->set_state(static_cast<ConnectionState>(next_state));

    *bytes_available = buffer->get_data_length();
}

void PacketHandshakingInHandshake::handle_legacy(const std::shared_ptr<Connection> &conn,
                                                 const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {

}
