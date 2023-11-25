#include "TagByteArray.h"

TagByteArray TagByteArray::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagByteArray TagByteArray::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";

    int32_t length = buffer.read_be_int();
    std::list<int8_t> items;
    for (int i = 0; i < length; i++) {
        items.push_back(buffer.read_byte());
    }

    return {name, items};
}

void TagByteArray::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_int(static_cast<int32_t>(m_value.size()));
    for (auto& datum : m_value) {
        buffer.write_byte(datum);
    }
}

std::list<int8_t> TagByteArray::get_value() const {
    return m_value;
}

icu::UnicodeString TagByteArray::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " [" + icu::UnicodeString::fromUTF8(std::to_string(get_value().size()))) + " bytes]";
}
