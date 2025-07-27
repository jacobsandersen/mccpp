#ifndef MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H
#define MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H

#include "../../OutboundPacket.h"

namespace celerity::net::configuration {
class PacketConfigurationOutKeepAlive : public OutboundPacket {
 public:
  PacketConfigurationOutKeepAlive() : OutboundPacket(0x04) {}

  void write_data(const std::shared_ptr<Connection>& conn,
                  ByteBuffer& buffer) override;
};
}  // namespace celerity::net::configuration

#endif  // MCCPP_PACKETCONFIGURATIONOUTKEEPALIVE_H
