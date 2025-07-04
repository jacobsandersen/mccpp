//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININLOGINSTART_H
#define MCCPP_PACKETLOGININLOGINSTART_H


#include <memory>
#include "../../Connection.h"
#include "../../../ByteBuffer.h"
#include "../../InboundPacket.h"

class PacketLoginInLoginStart : public InboundPacket
{
public:
    void handle(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&) override;
};


#endif //MCCPP_PACKETLOGININLOGINSTART_H
