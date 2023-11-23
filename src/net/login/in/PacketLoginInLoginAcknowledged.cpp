#include "PacketLoginInLoginAcknowledged.h"
#include "../../configuration/out/PacketConfigurationOutKeepAlive.h"

void PacketLoginInLoginAcknowledged::handle(const std::shared_ptr<Connection> &conn,
                                            const std::unique_ptr<ByteBuffer> &buffer) {

    conn->set_state(ConnectionState::Configuration);

    PacketConfigurationOutKeepAlive keep_alive;
    keep_alive.send(conn);
}