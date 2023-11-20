#ifndef MCCPP_PACKETLOGININLOGINACKNOWLEDGED_H
#define MCCPP_PACKETLOGININLOGINACKNOWLEDGED_H


#include "../../Connection.h"
#include "../../ByteBuffer.h"

class PacketLoginInLoginAcknowledged {
public:
    static void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &, size_t *);
};


#endif
