//
// Created by Jacob Andersen on 7/19/25.
//

#include "TagEnd.h"

namespace celerity::nbt::tag {
void TagEnd::create_and_write(ByteBuffer& buffer) {
  TagEnd().write(buffer, false);
}
}  // namespace celerity::nbt::tag
