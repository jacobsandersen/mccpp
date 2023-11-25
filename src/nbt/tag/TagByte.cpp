#include <iostream>
#include <unicode/decimfmt.h>
#include "TagByte.h"

TagByte TagByte::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagByte TagByte::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    int8_t value = buffer.read_byte();
    return {name, value};
}

void TagByte::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_byte(m_value);
}

int8_t TagByte::get_value() const {
    return m_value;
}

icu::UnicodeString TagByte::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
