#ifndef MCCPP_CONFIGURATIONPACKETHANDLER_H
#define MCCPP_CONFIGURATIONPACKETHANDLER_H


#include "../Connection.h"
#include "../ByteBuffer.h"

class ConfigurationPacketHandler {
public:
    static void handle_configuration_packet(const std::shared_ptr<Connection>&, const std::unique_ptr<ByteBuffer>&, size_t*);
};


#endif
