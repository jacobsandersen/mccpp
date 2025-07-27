//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGLIST_H
#define CELERITY_NBT_TAG_TAGLIST_H

#include "../Concepts.h"
#include "Tag.h"
#include "TagType.h"

namespace celerity::nbt::tag {
template <typename T>
  requires DerivedTag<T> && (!IsTagEnd<T>)
class TagList final : public Tag {
 public:
  explicit TagList(TagType child_type) : TagList("", child_type) {}
  TagList(const icu::UnicodeString& name, TagType child_type)
      : Tag(TagType::List, std::move(name)),
        m_child_type(std::move(child_type)) {}

  void add(T tag) {
    static_assert(m_child_type == tag.get_type());
    m_internal_list.push_back(tag);
  }

  void write_payload(ByteBuffer& buffer) const override {
    auto type = m_child_type;
    if (m_internal_list.empty()) {
      type = TagType::End;
    }

    if (m_internal_list.size() > std::numeric_limits<int32_t>::max()) {
      throw std::overflow_error(
          "TagList::write_payload: list too large, unable to write signed "
          "4-byte length prefix");
    }

    buffer.write_ubyte(type.get_type_id());
    buffer.write_int(m_internal_list.size());
    for (const auto& member : m_internal_list) {
      member.write_payload(buffer);
    }
  }

 private:
  TagType m_child_type;
  std::vector<T> m_internal_list;
};
}  // namespace celerity::nbt::tag

#endif
