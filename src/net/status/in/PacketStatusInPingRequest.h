//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_PACKETSTATUSINPINGREQUEST_H
#define MCCPP_PACKETSTATUSINPINGREQUEST_H

#include "../../InboundPacket.h"

class PacketStatusInPingRequest : public InboundPacket {
public:
    void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &) override;
};


#endif
