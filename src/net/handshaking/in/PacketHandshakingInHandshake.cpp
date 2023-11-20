#include "PacketHandshakingInHandshake.h"
#include <iostream>

void PacketHandshakingInHandshake::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t protocol_version = buffer->read_varint();
    std::cout << "Got protocol version: " << protocol_version << std::endl;

    std::string server_address = buffer->read_string();

    std::cout << "Got server address: \"" << server_address << "\"" << std::endl;

    uint16_t server_port = buffer->read_short();
    server_port = be16toh(server_port);
    std::cout << "Got server port: " << server_port << std::endl;

    int32_t next_state = buffer->read_varint();
    std::cout << "Got next m_state: " << next_state << std::endl;

    std::cout << "Setting connection m_state..." << std::endl;
    conn->set_state(static_cast<ConnectionState>(next_state));

    *bytes_available = buffer->get_data_length();
}

void PacketHandshakingInHandshake::handle_legacy(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {

}
