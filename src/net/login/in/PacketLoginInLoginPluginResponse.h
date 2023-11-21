#ifndef MCCPP_PACKETLOGININLOGINPLUGINRESPONSE_H
#define MCCPP_PACKETLOGININLOGINPLUGINRESPONSE_H


#include "../../Connection.h"
#include "../../ByteBuffer.h"
#include "../../InboundPacket.h"

class PacketLoginInLoginPluginResponse : public InboundPacket {
public:
    void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &) override;
};


#endif
