#include "PacketHandshakingInHandshake.h"

#include <glog/logging.h>

void PacketHandshakingInHandshake::handle(const std::shared_ptr<Connection>& conn,
                                          const std::unique_ptr<ByteBuffer>& buffer)
{
    LOG(INFO) << "Connection is open for handshaking...";

    int32_t protocol_version = buffer->read_varint();
    std::string server_address = buffer->read_string();
    uint16_t server_port = buffer->read_be_ushort();
    int32_t next_state = buffer->read_varint();

    std::string next_state_summary;
    switch (next_state)
    {
    case 1:
        next_state_summary = "Status";
        break;
    case 2:
        next_state_summary = "Login";
        break;
    case 3:
    default:
        LOG(WARNING) <<
            "Connection requested next state unknown or 3 (transfer) which is not supported. Connection closed.";
        conn->unclean_close();
        break;
    }

    LOG(INFO) << "Client requests next state: " << next_state_summary << ". Switching.";
    conn->set_state(static_cast<ConnectionState>(next_state));
}
