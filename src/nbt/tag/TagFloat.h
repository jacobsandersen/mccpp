//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGFLOAT_H
#define TAGFLOAT_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagFloat final : public Tag {
 public:
  explicit TagFloat(const float value) : TagFloat("", value) {}
  TagFloat(icu::UnicodeString name, const float value)
      : Tag(TagType::Float, std::move(name)), m_value(value) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  float m_value;
};
}  // namespace celerity::nbt::tag

#endif  // TAGFLOAT_H
