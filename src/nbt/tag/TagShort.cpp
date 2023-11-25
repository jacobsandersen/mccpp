#include "TagShort.h"

TagShort TagShort::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagShort TagShort::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    short value = buffer.read_be_short();
    return {name, value};
}

void TagShort::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_short(m_value);
}

int16_t TagShort::get_value() const {
    return m_value;
}

icu::UnicodeString TagShort::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
