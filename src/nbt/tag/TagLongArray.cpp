#include "TagLongArray.h"

void TagLongArray::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_int(static_cast<int32_t>(m_value.size()));
    for (auto& datum : m_value) {
        buffer.write_be_long(datum);
    }
}

std::list<int64_t> TagLongArray::get_value() const {
    return m_value;
}
