//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagShort.h"

void TagShort::write_payload(ByteBuffer& buffer) const
{
    buffer.write_short(m_value);
}
