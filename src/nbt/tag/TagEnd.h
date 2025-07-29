//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGEND_H
#define CELERITY_NBT_TAG_TAGEND_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagEnd final : public Tag {
 public:
  TagEnd() : Tag(TagType::End) {}
};
}  // namespace celerity::nbt::tag

#endif
