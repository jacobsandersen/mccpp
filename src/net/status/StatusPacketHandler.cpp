#include <glog/logging.h>
#include "StatusPacketHandler.h"
#include "in/PacketStatusInStatusRequest.h"
#include "in/PacketStatusInPingRequest.h"

void StatusPacketHandler::handle_status_packet(const std::shared_ptr<Connection> &conn,
                                               const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    LOG(INFO) << "Status packet length: " << length;

    int32_t packet_id = buffer->read_varint();
    LOG(INFO) << "Got Status packet id: " << packet_id;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0:
            LOG(INFO) << "Status Request packet received";
            PacketStatusInStatusRequest::handle(conn, buffer, bytes_available);
            break;
        case 1:
            LOG(INFO) << "Ping Request packet received";
            PacketStatusInPingRequest::handle(conn, buffer, bytes_available);
            break;
        default:
            throw std::runtime_error("Illegal status packet received.");
    }
}
