#ifndef MCCPP_PACKETCONFIGURATIONINPLUGINMESSAGE_H
#define MCCPP_PACKETCONFIGURATIONINPLUGINMESSAGE_H

#include "../../InboundPacket.h"

namespace celerity::net::configuration {
class PacketConfigurationInPluginMessage : public InboundPacket {
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::configuration

#endif  // MCCPP_PACKETCONFIGURATIONINPLUGINMESSAGE_H
