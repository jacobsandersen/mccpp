//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagDouble.h"

void TagDouble::write_payload(ByteBuffer& buffer) const
{
    buffer.write_double(m_value);
}
