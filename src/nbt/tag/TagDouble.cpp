#include "TagDouble.h"

TagDouble TagDouble::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagDouble TagDouble::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    double value = buffer.read_be_double();
    return {name, value};
}

void TagDouble::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_double(m_value);
}

double TagDouble::get_value() const {
    return m_value;
}

icu::UnicodeString TagDouble::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
