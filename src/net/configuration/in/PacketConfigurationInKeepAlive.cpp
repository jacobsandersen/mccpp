#include <glog/logging.h>
#include "PacketConfigurationInKeepAlive.h"
#include "../out/PacketConfigurationOutDisconnect.h"
#include "../out/PacketConfigurationOutKeepAlive.h"

void PacketConfigurationInKeepAlive::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Received a keep alive response";
    int64_t payload = buffer->read_long();

    if (conn->get_last_keep_alive_payload() != payload) {
        LOG(WARNING) << "Client did not respond with correct payload";

        PacketConfigurationOutDisconnect disconnect("Client responded with invalid Keep Alive");
        disconnect.send(conn);
        return;
    }

    LOG(INFO) << "Client responded correctly, it's still alive";

    LOG(INFO) << "Starting timeout for next keep alive dispatch";
    conn->start_new_timer(std::chrono::seconds(15), [conn](){
        if (conn->get_state() != ConnectionState::Configuration) {
            LOG(INFO) << "Server no longer in configuration state. Will not send a new configuration keep alive.";
            return;
        }

        LOG(INFO) << "Sending new keep alive";

        PacketConfigurationOutKeepAlive new_keep_alive;
        new_keep_alive.send(conn);
    });
}
