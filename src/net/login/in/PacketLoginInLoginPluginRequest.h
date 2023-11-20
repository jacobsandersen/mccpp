#ifndef MCCPP_PACKETLOGININLOGINPLUGINREQUEST_H
#define MCCPP_PACKETLOGININLOGINPLUGINREQUEST_H


#include "../../Connection.h"
#include "../../ByteBuffer.h"

class PacketLoginInLoginPluginRequest {
public:
    static void handle(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
};


#endif
