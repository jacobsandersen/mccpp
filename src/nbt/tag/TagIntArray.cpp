#include "TagIntArray.h"

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
