#ifndef CELERITY_NET_LOGIN_PACKETLOGININLOGINPLUGINRESPONSE_H
#define CELERITY_NET_LOGIN_PACKETLOGININLOGINPLUGINRESPONSE_H

#include "../../../ByteBuffer.h"
#include "../../Connection.h"
#include "../../InboundPacket.h"

namespace celerity::net::login {
class PacketLoginInLoginPluginResponse : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::login

#endif
