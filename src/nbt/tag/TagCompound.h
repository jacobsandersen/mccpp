//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGCOMPOUND_H
#define CELERITY_NBT_TAG_TAGCOMPOUND_H

#include "../Concepts.h"
#include "Tag.h"

namespace celerity::nbt::tag {
class TagCompound final : public Tag {
 public:
  TagCompound() : TagCompound("") {}
  explicit TagCompound(icu::UnicodeString name)
      : Tag(TagType::Compound, std::move(name)) {}

  template <typename T>
    requires DerivedTag<T> && (!IsTagEnd<T>)
  void add(T value) {
    m_internal_list.push_back(std::make_unique<T>(std::forward<T>(value)));
  }

  void write_payload(ByteBuffer& buffer) const override;

 private:
  std::vector<std::unique_ptr<Tag>> m_internal_list;
};
}  // namespace celerity::nbt::tag

#endif
