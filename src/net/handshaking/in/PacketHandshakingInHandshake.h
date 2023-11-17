//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_PACKETHANDSHAKINGINHANDSHAKE_H
#define MCCPP_PACKETHANDSHAKINGINHANDSHAKE_H

#include "../../Packet.h"

class PacketHandshakingInHandshake {
public:
    static void handle(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
    static void handle_legacy(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
};


#endif
