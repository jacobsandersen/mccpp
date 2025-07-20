//
// Created by Jacob Andersen on 7/4/25.
//

#ifndef MCCPP_PACKETCONFIGURATIONINKNOWNPACKS_H
#define MCCPP_PACKETCONFIGURATIONINKNOWNPACKS_H
#include "../../InboundPacket.h"

class PacketConfigurationInKnownPacks final : public InboundPacket
{
public:
    void handle(const std::shared_ptr<Connection>& conn, const std::unique_ptr<ByteBuffer>& buffer) override;
};


#endif //MCCPP_PACKETCONFIGURATIONINKNOWNPACKS_H
