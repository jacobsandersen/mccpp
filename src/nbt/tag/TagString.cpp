#include "TagString.h"

void TagString::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_string_modified_utf8(m_value);
}

std::wstring TagString::get_value() const {
    return m_value;
}
