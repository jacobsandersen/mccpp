//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagLong.h"

void TagLong::write_payload(ByteBuffer& buffer) const
{
    buffer.write_long(m_value);
}
