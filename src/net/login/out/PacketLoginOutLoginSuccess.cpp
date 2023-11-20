#include "PacketLoginOutLoginSuccess.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketLoginOutLoginSuccess::send(const std::shared_ptr<Connection> &conn) const {
    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(2);

    if (m_username.length() > 16) {
        throw std::invalid_argument("Tried to send login success with username longer than 16 characters.");
    }

    ByteBuffer buf;
    buf.write_uuid(m_unique_id);
    buf.write_string(m_username, m_username.length());
    buf.write_varint(static_cast<int32_t>(m_properties.size()));
    for (const auto& prop : m_properties) {
        buf.write_string(prop.name);
        buf.write_string(prop.value);
        buf.write_boolean(prop.is_signed());
        if (prop.is_signed()) {
            buf.write_string(prop.signature);
        }
    }

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
