#include "PacketStatusOutPingResponse.h"

void PacketStatusOutPingResponse::write_data(ByteBuffer &buffer) {
    buffer.write_long(m_ping_payload);
}
