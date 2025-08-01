#ifndef CELERITY_NET_LOGIN_PACKETLOGINOUTSETCOMPRESSION_H
#define CELERITY_NET_LOGIN_PACKETLOGINOUTSETCOMPRESSION_H

#include "../../OutboundPacket.h"

namespace celerity::net::login {
class PacketLoginOutSetCompression : public OutboundPacket {
 public:
  PacketLoginOutSetCompression() : OutboundPacket(0x03) {}

  void write_data(const std::shared_ptr<Connection>& conn,
                  ByteBuffer& buffer) override;
};
}  // namespace celerity::net::login
#endif
