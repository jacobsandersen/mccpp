#include <glog/logging.h>
#include "PacketConfigurationOutKeepAlive.h"
#include "PacketConfigurationOutDisconnect.h"

void PacketConfigurationOutKeepAlive::write_data(const std::shared_ptr<Connection> &conn, ByteBuffer &buffer) {
    int64_t payload = std::time(nullptr);
    buffer.write_long(payload);

    LOG(INFO) << "Sending a configuration keep alive with value: " << payload << ". Client must respond within 30 seconds.";
    conn->set_last_keep_alive_payload(payload);

    LOG(INFO) << "Starting keep alive response timer";
    conn->start_new_timer(std::chrono::seconds(30), [conn](){
        LOG(WARNING) << "Client did not respond to keep alive.";

        PacketConfigurationOutDisconnect disconnect("Client did not respond to Keep Alive");
        disconnect.send(conn);
    });
}
