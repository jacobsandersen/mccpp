#include "TagInt.h"

void TagInt::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_int(htobe32(m_value));
}

int32_t TagInt::get_value() const {
    return m_value;
}
