#include "PacketConfigurationOutKeepAlive.h"
#include "PacketConfigurationOutDisconnect.h"

void PacketConfigurationOutKeepAlive::write_data(const std::shared_ptr<Connection> &conn, ByteBuffer &buffer) {
    int64_t payload = std::time(nullptr);
    buffer.write_long(payload);

    conn->set_last_keep_alive_payload(payload);

    conn->start_new_timer(std::chrono::seconds(30), [conn](){
        PacketConfigurationOutDisconnect disconnect("Client did not respond to Keep Alive");
        disconnect.send(conn);
    });
}
