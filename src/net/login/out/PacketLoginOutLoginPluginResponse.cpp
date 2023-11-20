#include "PacketLoginOutLoginPluginResponse.h"
#include "../../ByteBuffer.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketLoginOutLoginPluginResponse::send(const std::shared_ptr<Connection> &conn) const {
    ByteBuffer buf;
    buf.write_varint(m_message_id);
    buf.write_boolean(m_successful);
    buf.write_ubytes(m_bytes.data(), m_bytes.size());

    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(2);
    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
