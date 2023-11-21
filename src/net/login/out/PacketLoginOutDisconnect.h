#ifndef MCCPP_PACKETLOGINOUTDISCONNECT_H
#define MCCPP_PACKETLOGINOUTDISCONNECT_H

#include <string>
#include <memory>
#include <utility>
#include "../../Connection.h"
#include "../../OutboundPacket.h"

class PacketLoginOutDisconnect : public OutboundPacket {
public:
    explicit PacketLoginOutDisconnect(std::string reason) : OutboundPacket(0x00), m_reason(std::move(reason)) {}

    void write_data(ByteBuffer&) override;
private:
    std::string m_reason;
};

#endif
