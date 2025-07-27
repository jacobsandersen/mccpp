//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGEND_H
#define TAGEND_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagEnd final : public Tag {
 public:
  TagEnd() : Tag(TagType::End) {}

  static void create_and_write(ByteBuffer& buffer);
  void write_payload(ByteBuffer& buffer) const override {}  // No payload
};
}  // namespace celerity::nbt::tag

#endif  // TAGEND_H
