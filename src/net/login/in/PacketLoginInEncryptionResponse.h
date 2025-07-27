//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
#define MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H

#include <memory>

#include "../../../ByteBuffer.h"
#include "../../Connection.h"
#include "../../InboundPacket.h"

namespace celerity::net::login {
class PacketLoginInEncryptionResponse : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::login

#endif  // MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
