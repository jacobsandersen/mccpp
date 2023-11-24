#include "TagDouble.h"

void TagDouble::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);

    uint64_t encoded;
    std::memcpy(&encoded, &m_value, sizeof(encoded));
    encoded = htobe64(encoded);
    buffer.write_ulong(encoded);
}

double TagDouble::get_value() const {
    return m_value;
}
