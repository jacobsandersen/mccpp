#include "TagLong.h"

TagLong TagLong::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagLong TagLong::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    int64_t value = buffer.read_be_long();
    return {name, value};
}

void TagLong::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_long(m_value);
}

int64_t TagLong::get_value() const {
    return m_value;
}

icu::UnicodeString TagLong::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
