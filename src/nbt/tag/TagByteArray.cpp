//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagByteArray.h"

namespace celerity::nbt::tag {
void TagByteArray::write_payload(ByteBuffer& buffer) const {
  if (m_data.size() > std::numeric_limits<int32_t>::max()) {
    throw std::overflow_error(
        "TagByteArray::write_payload: byte array too large, unable to write "
        "signed 4-byte length prefix");
  }

  buffer.write_int(static_cast<int32_t>(m_data.size()));
  for (const int8_t datum : m_data) {
    buffer.write_byte(datum);
  }
}
}  // namespace celerity::nbt::tag
