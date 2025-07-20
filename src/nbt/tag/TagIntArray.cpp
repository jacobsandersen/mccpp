//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagIntArray.h"

void TagIntArray::write_payload(ByteBuffer& buffer) const
{
    if (m_data.size() > std::numeric_limits<int32_t>::max())
    {
        throw std::overflow_error("TagIntArray::write_payload: int array too large, unable to write signed 4-byte length prefix");
    }

    buffer.write_int(static_cast<int32_t>(m_data.size()));
    for (const int32_t datum : m_data)
    {
        buffer.write_int(datum);
    }
}
