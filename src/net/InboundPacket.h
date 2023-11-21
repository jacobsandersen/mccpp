#ifndef MCCPP_INBOUNDPACKET_H
#define MCCPP_INBOUNDPACKET_H


#include "Connection.h"
#include "ByteBuffer.h"

class InboundPacket {
public:
    virtual void handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) = 0;
    virtual ~InboundPacket() = default;
};


#endif
