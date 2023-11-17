#include <iostream>
#include "StatusPacketHandler.h"
#include "in/PacketStatusInStatusRequest.h"
#include "in/PacketStatusInPingRequest.h"

void StatusPacketHandler::handle_status_packet(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    std::cout << "Got status packet length: " << length << std::endl;

    int32_t packet_id = buffer->read_varint();
    std::cout << "Got status packet id: " << packet_id << std::endl;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0:
            std::cout << "Status request packet received" << std::endl;
            PacketStatusInStatusRequest::handle(conn, buffer, bytes_available);
            break;
        case 1:
            std::cout << "Ping request packet received" << std::endl;
            PacketStatusInPingRequest::handle(conn, buffer, bytes_available);
            break;
        default:
            throw std::runtime_error("Illegal status packet received.");
    }
}
