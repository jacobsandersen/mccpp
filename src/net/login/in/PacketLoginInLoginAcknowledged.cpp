#include <glog/logging.h>
#include "PacketLoginInLoginAcknowledged.h"
#include "../../configuration/out/PacketConfigurationOutKeepAlive.h"

void PacketLoginInLoginAcknowledged::handle(const std::shared_ptr<Connection> &conn,
                                            const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Login acknowledged. Setting connection state to Configuration...";
    conn->set_state(ConnectionState::Configuration);

    LOG(INFO) << "Beginning configuration keep alives...";
    PacketConfigurationOutKeepAlive keep_alive;
    keep_alive.send(conn);
}