#include <glog/logging.h>
#include "LoginPacketHandler.h"
#include "in/PacketLoginInLoginStart.h"
#include "in/PacketLoginInEncryptionResponse.h"
#include "in/PacketLoginInLoginAcknowledged.h"
#include "in/PacketLoginInLoginPluginRequest.h"

void LoginPacketHandler::handle_login_packet(const std::shared_ptr<Connection> &conn,
                                             const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    LOG(INFO) << "Login packet length: " << length;

    int32_t packet_id = buffer->read_varint();
    LOG(INFO) << "Got Login packet id: " << packet_id;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        case 0x0:
            LOG(INFO) << "Login Start packet received";
            PacketLoginInLoginStart::handle(conn, buffer, bytes_available);
            break;
        case 0x1:
            LOG(INFO) << "Encryption Response packet received";
            PacketLoginInEncryptionResponse::handle(conn, buffer, bytes_available);
            break;
        case 0x2:
            LOG(INFO) << "Login Plugin Request packet received";
            PacketLoginInLoginPluginRequest::handle(conn, buffer, bytes_available);
            break;
        case 0x3:
            LOG(INFO) << "Login Acknowledged packet received";
            PacketLoginInLoginAcknowledged::handle(conn, buffer, bytes_available);
            break;
        default:
            throw std::runtime_error("Illegal login packet received.");
    }
}
