#include <iostream>
#include "PacketLoginInLoginAcknowledged.h"

void PacketLoginInLoginAcknowledged::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    std::cout << "Setting connection state to configuration" << std::endl;
    conn->set_state(ConnectionState::Configuration);
}