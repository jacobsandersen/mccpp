#ifndef MCCPP_PACKETCONFIGURATIONINKEEPALIVE_H
#define MCCPP_PACKETCONFIGURATIONINKEEPALIVE_H

#include "../../InboundPacket.h"

namespace celerity::net::configuration {
class PacketConfigurationInKeepAlive : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>& conn,
              const std::unique_ptr<ByteBuffer>& buffer) override;
};
}  // namespace celerity::net::configuration

#endif  // MCCPP_PACKETCONFIGURATIONINKEEPALIVE_H
