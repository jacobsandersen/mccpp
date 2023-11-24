#include "TagByte.h"

void TagByte::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_byte(m_value);
}

int8_t TagByte::get_value() const {
    return m_value;
}
