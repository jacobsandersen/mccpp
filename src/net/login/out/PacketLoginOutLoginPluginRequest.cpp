#include "PacketLoginOutLoginPluginRequest.h"

void PacketLoginOutLoginPluginRequest::write_data(ByteBuffer &buffer) {
    buffer.write_varint(m_message_id);
    buffer.write_boolean(m_successful);
    buffer.write_ubytes(m_bytes.data(), m_bytes.size());
}
