#ifndef CELERITY_NET_CONFIGURATION_PACKETCONFIGURATIONINCLIENTINFORMATION_H
#define CELERITY_NET_CONFIGURATION_PACKETCONFIGURATIONINCLIENTINFORMATION_H

#include "../../InboundPacket.h"

namespace celerity::net::configuration {
class PacketConfigurationInClientInformation : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::configuration

#endif
