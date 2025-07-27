//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETSTATUSOUTPINGRESPONSE_H
#define MCCPP_PACKETSTATUSOUTPINGRESPONSE_H

#include <cstdint>
#include <memory>

#include "../../Connection.h"
#include "../../OutboundPacket.h"

namespace celerity::net::status {
class PacketStatusOutPingResponse : public OutboundPacket {
 public:
  explicit PacketStatusOutPingResponse(int64_t ping_payload)
      : OutboundPacket(0x01), m_ping_payload(ping_payload) {}

  void write_data(const std::shared_ptr<Connection> &conn,
                  ByteBuffer &buffer) override;

 private:
  int64_t m_ping_payload;
};
}  // namespace celerity::net::status

#endif  // MCCPP_PACKETSTATUSOUTPINGRESPONSE_H
