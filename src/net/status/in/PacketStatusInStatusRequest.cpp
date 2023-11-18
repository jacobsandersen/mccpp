#include "PacketStatusInStatusRequest.h"
#include "../out/PacketStatusOutStatusResponse.h"

void PacketStatusInStatusRequest::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    PacketStatusOutStatusResponse resp("1.20.2", 764, 100,
                                       0, "A C++ Minecraft Server", "",
                                       std::map<std::string, std::string>(), false, false);

    resp.send(conn);
}
