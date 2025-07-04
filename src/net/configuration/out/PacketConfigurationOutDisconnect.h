#ifndef MCCPP_PACKETCONFIGURATIONOUTDISCONNECT_H
#define MCCPP_PACKETCONFIGURATIONOUTDISCONNECT_H


#include <utility>

#include "../../OutboundPacket.h"

class PacketConfigurationOutDisconnect : public OutboundPacket
{
public:
    explicit PacketConfigurationOutDisconnect(std::string reason) : OutboundPacket(0x02), m_reason(std::move(reason))
    {
    }

    void write_data(const std::shared_ptr<Connection>&, ByteBuffer&) override;

private:
    std::string m_reason;
};


#endif //MCCPP_PACKETCONFIGURATIONOUTDISCONNECT_H
