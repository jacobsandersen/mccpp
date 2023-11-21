#include <glog/logging.h>
#include "PacketStatusInPingRequest.h"
#include "../out/PacketStatusOutPingResponse.h"

void
PacketStatusInPingRequest::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Received a Status Ping Request. Responding.";
    PacketStatusOutPingResponse resp(buffer->read_long());
    resp.send(conn);
}