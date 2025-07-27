//
// Created by simple on 11/10/23.
//

#ifndef CELERITY_NET_HANDSHAKING_PACKETHANDSHAKINGINHANDSHAKE_H
#define CELERITY_NET_HANDSHAKING_PACKETHANDSHAKINGINHANDSHAKE_H

#include "../../InboundPacket.h"

namespace celerity::net::handshaking {
class PacketHandshakingInHandshake : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection>&,
              const std::unique_ptr<ByteBuffer>&) override;
};
}  // namespace celerity::net::handshaking

#endif
