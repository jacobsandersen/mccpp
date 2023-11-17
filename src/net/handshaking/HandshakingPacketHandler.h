//
// Created by simple on 11/16/23.
//

#ifndef MCCPP_HANDSHAKINGPACKETHANDLER_H
#define MCCPP_HANDSHAKINGPACKETHANDLER_H


#include "../Connection.h"
#include "../ByteBuffer.h"

class HandshakingPacketHandler {
public:
    static void handle_handshaking_packet(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
};

#endif
