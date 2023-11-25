#include "TagFloat.h"

TagFloat TagFloat::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagFloat TagFloat::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    float value = buffer.read_be_float();
    return {name, value};
}

void TagFloat::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_float(m_value);
}

float TagFloat::get_value() const {
    return m_value;
}

icu::UnicodeString TagFloat::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
