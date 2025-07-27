//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagCompound.h"

namespace celerity::nbt::tag {
void TagCompound::write_payload(ByteBuffer& buffer) const {
  for (const auto& elem : m_internal_list) {
    if (elem->get_name().isBogus()) {
      throw std::runtime_error("A child of a compound tag must have a name.");
    }

    elem->write(buffer);
  }

  TagEnd::create_and_write(buffer);
}
}  // namespace celerity::nbt::tag