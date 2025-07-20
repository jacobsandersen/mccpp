//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagLongArray.h"

void TagLongArray::write_payload(ByteBuffer& buffer) const
{
    if (m_data.size() > std::numeric_limits<int32_t>::max())
    {
        throw std::overflow_error("TagLongArray::write_payload: long array too large, unable to write signed 4-byte length prefix");
    }

    buffer.write_int(static_cast<int32_t>(m_data.size()));
    for (const int64_t datum : m_data)
    {
        buffer.write_long(datum);
    }
}
