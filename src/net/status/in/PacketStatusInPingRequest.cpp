#include "PacketStatusInPingRequest.h"

#include <glog/logging.h>

#include "../out/PacketStatusOutPingResponse.h"

namespace celerity::net::status {
void PacketStatusInPingRequest::handle(
    const std::shared_ptr<Connection>& conn,
    const std::unique_ptr<ByteBuffer>& buffer) {
  LOG(INFO) << "Received ping request. Pong.";

  PacketStatusOutPingResponse resp(buffer->read_be_long());
  resp.send(conn);
}
}  // namespace celerity::net::status
