//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagInt.h"

void TagInt::write_payload(ByteBuffer& buffer) const
{
    buffer.write_int(m_value);
}
