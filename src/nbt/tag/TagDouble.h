//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGDOUBLE_H
#define CELERITY_NBT_TAG_TAGDOUBLE_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagDouble final : public Tag {
 public:
  explicit TagDouble(const double value) : TagDouble("", value) {}
  TagDouble(icu::UnicodeString name, const double value)
      : Tag(TagType::Double, std::move(name)), m_value(value) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  double m_value;
};
}  // namespace celerity::nbt::tag

#endif
