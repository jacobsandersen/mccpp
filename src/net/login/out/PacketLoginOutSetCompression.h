#ifndef MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
#define MCCPP_PACKETLOGINOUTSETCOMPRESSION_H


#include "../../OutboundPacket.h"

class PacketLoginOutSetCompression : public OutboundPacket {
public:
    PacketLoginOutSetCompression() : OutboundPacket(0x03) {}

    void write_data(ByteBuffer&) override;
};


#endif //MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
