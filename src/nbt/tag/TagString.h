//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGSTRING_H
#define CELERITY_NBT_TAG_TAGSTRING_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagString final : public Tag {
 public:
  explicit TagString(icu::UnicodeString value)
      : TagString("", std::move(value)) {}
  TagString(icu::UnicodeString name, icu::UnicodeString value)
      : Tag(TagType::String, std::move(name)), m_value(std::move(value)) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  icu::UnicodeString m_value;
};
}  // namespace celerity::nbt::tag

#endif
