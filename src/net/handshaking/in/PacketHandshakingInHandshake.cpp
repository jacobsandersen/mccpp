#include "PacketHandshakingInHandshake.h"

#include <glog/logging.h>

void PacketHandshakingInHandshake::handle(const std::shared_ptr<Connection>& conn,
                                          const std::unique_ptr<ByteBuffer>& buffer)
{
    LOG(INFO) << "handshakingInHandshake::handle";

    int32_t protocol_version = buffer->read_varint();
    std::string server_address = buffer->read_string();
    uint16_t server_port = buffer->read_be_ushort();
    int32_t next_state = buffer->read_varint();

    LOG(INFO) << "requested next state " << next_state;

    conn->set_state(static_cast<ConnectionState>(next_state));
}
