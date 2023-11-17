#include <iostream>
#include "PacketStatusOutPingResponse.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketStatusOutPingResponse::send(const std::shared_ptr<Connection> &conn) const {
    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(1);

    ByteBuffer buf;
    buf.write_long(m_ping_payload);

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
