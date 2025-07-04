#ifndef MCCPP_PACKETLOGININLOGINACKNOWLEDGED_H
#define MCCPP_PACKETLOGININLOGINACKNOWLEDGED_H


#include "../../Connection.h"
#include "../../../ByteBuffer.h"
#include "../../InboundPacket.h"

class PacketLoginInLoginAcknowledged : public InboundPacket
{
public:
    void handle(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&) override;
};


#endif
