//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagFloat.h"

void TagFloat::write_payload(ByteBuffer& buffer) const
{
    buffer.write_float(m_value);
}
