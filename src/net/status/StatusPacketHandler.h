//
// Created by simple on 11/16/23.
//

#ifndef MCCPP_STATUSPACKKETHANDLER_H
#define MCCPP_STATUSPACKKETHANDLER_H

#include "../Connection.h"
#include "../ByteBuffer.h"

class StatusPacketHandler {
public:
    static void
    handle_status_packet(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &, size_t *);
};

#endif
