//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagString.h"

void TagString::write_payload(ByteBuffer& buffer) const
{
    buffer.write_string_modified_utf8(m_value);
}
