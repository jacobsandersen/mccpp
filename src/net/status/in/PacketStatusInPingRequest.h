//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_PACKETSTATUSINPINGREQUEST_H
#define MCCPP_PACKETSTATUSINPINGREQUEST_H

#include "../../Packet.h"

class PacketStatusInPingRequest {
public:
    static void handle(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
};


#endif
