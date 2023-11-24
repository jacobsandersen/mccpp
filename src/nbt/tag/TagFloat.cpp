#include "TagFloat.h"

void TagFloat::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);

    uint32_t encoded;
    std::memcpy(&encoded, &m_value, sizeof(encoded));
    encoded = htobe32(encoded);
    buffer.write_uint(encoded);
}

float TagFloat::get_value() const {
    return m_value;
}
