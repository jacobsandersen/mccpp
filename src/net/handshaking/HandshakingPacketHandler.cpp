#include <glog/logging.h>
#include "HandshakingPacketHandler.h"
#include "in/PacketHandshakingInHandshake.h"

void HandshakingPacketHandler::handle_handshaking_packet(const std::shared_ptr<Connection> &conn,
                                                         const std::unique_ptr<ByteBuffer> &buffer,
                                                         size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    LOG(INFO) << "Handshaking packet length: " << length;

    int32_t packet_id = buffer->read_varint();
    LOG(INFO) << "Got Handshaking packet id: " << packet_id;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0:
            LOG(INFO) << "Standard Handshaking packet received";
            PacketHandshakingInHandshake::handle(conn, buffer, bytes_available);
            break;
        case 0xFE:
        default:
            throw std::runtime_error("Illegal handshaking packet received.");
    }
}
