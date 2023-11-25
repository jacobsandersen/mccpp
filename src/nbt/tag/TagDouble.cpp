#include "TagDouble.h"

void TagDouble::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_double(m_value);
}

double TagDouble::get_value() const {
    return m_value;
}
