#include "PacketConfigurationInKeepAlive.h"

#include <glog/logging.h>

#include "../out/PacketConfigurationOutDisconnect.h"
#include "../out/PacketConfigurationOutKeepAlive.h"

void PacketConfigurationInKeepAlive::handle(const std::shared_ptr<Connection>& conn,
                                            const std::unique_ptr<ByteBuffer>& buffer)
{
    int64_t payload = buffer->read_be_long();

    if (conn->get_last_keep_alive_payload() != payload)
    {
        PacketConfigurationOutDisconnect disconnect("Client responded with invalid Keep Alive");
        disconnect.send(conn);
        return;
    }

    conn->start_new_timer(std::chrono::seconds(15), [weak_conn = std::weak_ptr(conn)]()
    {
        if (const auto locked = weak_conn.lock())
        {
            if (locked->get_state() != ConnectionState::Configuration)
            {
                return;
            }

            PacketConfigurationOutKeepAlive new_keep_alive;
            new_keep_alive.send(locked);
        } else
        {
            LOG(WARNING) << "Configuration keep alive timer fired, but connection was no longer valid";
        }
    });
}
