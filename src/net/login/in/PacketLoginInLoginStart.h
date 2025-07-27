//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININLOGINSTART_H
#define MCCPP_PACKETLOGININLOGINSTART_H

#include <memory>

#include "../../../ByteBuffer.h"
#include "../../Connection.h"
#include "../../InboundPacket.h"

namespace celerity::net::login {
class PacketLoginInLoginStart : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::login

#endif  // MCCPP_PACKETLOGININLOGINSTART_H
