#include "PacketLoginOutDisconnect.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketLoginOutDisconnect::send(const std::shared_ptr<Connection> &conn) const {
    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(1);

    ByteBuffer buf;
    buf.write_string(m_reason);

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
