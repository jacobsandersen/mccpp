#include <iostream>
#include "LoginPacketHandler.h"
#include "in/PacketLoginInLoginStart.h"
#include "in/PacketLoginInEncryptionResponse.h"

void LoginPacketHandler::handle_login_packet(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    std::cout << "Got login packet length: " << length << std::endl;

    int32_t packet_id = buffer->read_varint();
    std::cout << "Got login packet id: " << packet_id << std::endl;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0:
            std::cout << "Login start packet received" << std::endl;
            PacketLoginInLoginStart::handle(conn, buffer, bytes_available);
            break;
        case 1:
            std::cout << "Encryption response packet received" << std::endl;
            PacketLoginInEncryptionResponse::handle(conn, buffer, bytes_available);
            break;
        default:
            throw std::runtime_error("Illegal login packet received.");
    }

}
