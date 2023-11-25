#include "TagFloat.h"

void TagFloat::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_float(m_value);
}

float TagFloat::get_value() const {
    return m_value;
}
