#ifndef MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
#define MCCPP_PACKETLOGINOUTSETCOMPRESSION_H


#include "../../OutboundPacket.h"

class PacketLoginOutSetCompression : public OutboundPacket
{
public:
    PacketLoginOutSetCompression() : OutboundPacket(0x03)
    {
    }

    void write_data(const std::shared_ptr<Connection>& conn, ByteBuffer& buffer) override;
};


#endif //MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
