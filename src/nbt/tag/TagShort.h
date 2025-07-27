//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGSHORT_H
#define CELERITY_NBT_TAG_TAGSHORT_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagShort final : public Tag {
 public:
  explicit TagShort(const int16_t value) : TagShort("", value) {}
  TagShort(icu::UnicodeString name, const int16_t value)
      : Tag(TagType::Short, std::move(name)), m_value(value) {};
  void write_payload(ByteBuffer& buffer) const override;

 private:
  int16_t m_value;
};
}  // namespace celerity::nbt::tag

#endif
