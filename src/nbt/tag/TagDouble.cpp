//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagDouble.h"

namespace celerity::nbt::tag {
void TagDouble::write_payload(ByteBuffer& buffer) const {
  buffer.write_double(m_value);
}
}  // namespace celerity::nbt::tag
