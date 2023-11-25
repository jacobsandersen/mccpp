#include "TagInt.h"

TagInt TagInt::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagInt TagInt::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    int32_t value = buffer.read_be_int();
    return {name, value};
}

void TagInt::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_int(m_value);
}

int32_t TagInt::get_value() const {
    return m_value;
}

icu::UnicodeString TagInt::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(std::to_string(get_value())));
}
