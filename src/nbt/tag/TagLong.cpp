#include "TagLong.h"

void TagLong::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_long(htobe64(m_value));
}

int64_t TagLong::get_value() const {
    return m_value;
}
