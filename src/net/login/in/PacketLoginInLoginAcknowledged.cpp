#include <glog/logging.h>
#include "PacketLoginInLoginAcknowledged.h"

void PacketLoginInLoginAcknowledged::handle(const std::shared_ptr<Connection> &conn,
                                            const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Setting connection state to Configuration...";
    conn->set_state(ConnectionState::Configuration);
}