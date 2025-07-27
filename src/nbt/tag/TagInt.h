//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGINT_H
#define TAGINT_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagInt final : public Tag {
 public:
  explicit TagInt(const int16_t value) : TagInt("", value) {}
  TagInt(icu::UnicodeString name, const int32_t value)
      : Tag(TagType::Int, std::move(name)), m_value(value) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  int32_t m_value;
};
}  // namespace celerity::nbt::tag

#endif  // TAGINT_H
