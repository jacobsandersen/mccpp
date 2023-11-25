#include "TagIntArray.h"

TagIntArray TagIntArray::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagIntArray TagIntArray::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";

    int32_t length = buffer.read_be_int();
    std::list<int32_t> items;
    for (int i = 0; i < length; i++) {
        items.push_back(buffer.read_be_int());
    }

    return {name, items};
}

void TagIntArray::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_int(static_cast<int32_t>(m_value.size()));
    for (auto& datum : m_value) {
        buffer.write_be_int(datum);
    }
}

std::list<int32_t> TagIntArray::get_value() const {
    return m_value;
}

icu::UnicodeString TagIntArray::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " [" + icu::UnicodeString::fromUTF8(std::to_string(get_value().size()))) + " ints]";
}
