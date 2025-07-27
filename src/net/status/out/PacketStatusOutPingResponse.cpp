#include "PacketStatusOutPingResponse.h"

namespace celerity::net::status {
void PacketStatusOutPingResponse::write_data(
    const std::shared_ptr<Connection>& conn, ByteBuffer& buffer) {
  buffer.write_long(m_ping_payload);
}
}  // namespace celerity::net::status
