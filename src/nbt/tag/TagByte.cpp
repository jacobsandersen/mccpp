//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagByte.h"

void TagByte::write_payload(ByteBuffer& buffer) const
{
    buffer.write_byte(m_byte);
}
