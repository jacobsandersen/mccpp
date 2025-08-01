//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGCOMPOUND_H
#define CELERITY_NBT_TAG_TAGCOMPOUND_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagCompound final : public Tag {
 public:
  TagCompound() : Tag(TagType::Compound) {}

  void add(const icu::UnicodeString& name, std::unique_ptr<Tag> value) {
    add({name, std::move(value)});
  }

  void add(NamedTag&& named_tag) {
    m_internal_list.push_back(std::move(named_tag));
  }

  [[nodiscard]] std::vector<NamedTag>& get_tags() {
    return m_internal_list;
  }
 private:
  std::vector<NamedTag> m_internal_list;
};
}  // namespace celerity::nbt::tag

#endif
