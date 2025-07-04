#include "PacketConfigurationInKeepAlive.h"
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

    conn->start_new_timer(std::chrono::seconds(15), [conn]()
    {
        if (conn->get_state() != ConnectionState::Configuration)
        {
            return;
        }

        PacketConfigurationOutKeepAlive new_keep_alive;
        new_keep_alive.send(conn);
    });
}
