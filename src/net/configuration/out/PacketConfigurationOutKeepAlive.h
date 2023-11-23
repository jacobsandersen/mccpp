#ifndef MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H
#define MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H


#include "../../OutboundPacket.h"

class PacketConfigurationOutKeepAlive : public OutboundPacket {
public:
    PacketConfigurationOutKeepAlive() : OutboundPacket(0x03) {}

    void write_data(const std::shared_ptr<Connection> &conn, ByteBuffer &buffer) override;
};


#endif //MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H
