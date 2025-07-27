#ifndef MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
#define MCCPP_PACKETLOGINOUTSETCOMPRESSION_H

#include "../../OutboundPacket.h"

namespace celerity::net::login {
class PacketLoginOutSetCompression : public OutboundPacket {
 public:
  PacketLoginOutSetCompression() : OutboundPacket(0x03) {}

  void write_data(const std::shared_ptr<Connection>& conn,
                  ByteBuffer& buffer) override;
};
}  // namespace celerity::net::login
#endif  // MCCPP_PACKETLOGINOUTSETCOMPRESSION_H
