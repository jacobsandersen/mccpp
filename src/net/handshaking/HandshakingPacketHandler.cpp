#include <iostream>
#include "HandshakingPacketHandler.h"
#include "in/PacketHandshakingInHandshake.h"

void HandshakingPacketHandler::handle_handshaking_packet(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    std::cout << "Got handshaking packet length: " << length << std::endl;

    int32_t packet_id = buffer->read_varint();
    std::cout << "Got handshaking packet id: " << packet_id << std::endl;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0:
            std::cout << "Standard handshaking packet received" << std::endl;
            PacketHandshakingInHandshake::handle(conn, buffer, bytes_available);
            break;
        case 0xFE:
        default:
            throw std::runtime_error("Illegal handshaking packet received.");
    }
}
