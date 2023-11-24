#include "TagShort.h"

void TagShort::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_short(htobe16(m_value));
}

int16_t TagShort::get_value() const {
    return m_value;
}
