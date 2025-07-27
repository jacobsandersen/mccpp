#ifndef CELERITY_NET_INBOUNDPACKET_H
#define CELERITY_NET_INBOUNDPACKET_H

#include "../ByteBuffer.h"
#include "Connection.h"

namespace celerity::net {
class InboundPacket {
 public:
  virtual void handle(const std::shared_ptr<Connection> &conn,
                      const std::unique_ptr<ByteBuffer> &buffer) = 0;
  virtual ~InboundPacket() = default;
};
}  // namespace celerity::net

#endif
