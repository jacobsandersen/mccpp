#include "PacketStatusInPingRequest.h"
#include "../out/PacketStatusOutPingResponse.h"

void
PacketStatusInPingRequest::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer,
                                  size_t *bytes_available) {
    PacketStatusOutPingResponse resp(buffer->read_long());
    resp.send(conn);
    *bytes_available = buffer->get_data_length();
}