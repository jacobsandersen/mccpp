//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_PACKETSTATUSINSTATUSREQUEST_H
#define MCCPP_PACKETSTATUSINSTATUSREQUEST_H

#include "../../InboundPacket.h"

namespace celerity::net::status {
class PacketStatusInStatusRequest : public InboundPacket {
 public:
  void handle(const std::shared_ptr<Connection> &,
              const std::unique_ptr<ByteBuffer> &) override;
};
}  // namespace celerity::net::status
#endif
