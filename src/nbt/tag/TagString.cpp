#include "TagString.h"

TagString TagString::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagString TagString::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    icu::UnicodeString value = buffer.read_string_modified_utf8();
    return {name, value};
}

void TagString::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_string_modified_utf8(m_value);
}

icu::UnicodeString TagString::get_value() const {
    return m_value;
}

icu::UnicodeString TagString::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " \"" + get_value() + "\"");
}
