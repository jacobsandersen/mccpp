#ifndef MCCPP_OUTBOUNDPACKET_H
#define MCCPP_OUTBOUNDPACKET_H

#include "../ByteBuffer.h"
#include "Connection.h"

namespace celerity::net {
class OutboundPacket {
 public:
  explicit OutboundPacket(const int32_t packet_id) : m_packet_id(packet_id) {}

  virtual ~OutboundPacket() = default;

  virtual void write_data(const std::shared_ptr<Connection>&, ByteBuffer&) = 0;

  void send(const std::shared_ptr<Connection>&);

 private:
  int32_t m_packet_id;
};
}  // namespace celerity::net

#endif
