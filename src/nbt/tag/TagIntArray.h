//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGINTARRAY_H
#define CELERITY_NBT_TAG_TAGINTARRAY_H

#include <utility>

#include "Tag.h"

namespace celerity::nbt::tag {
class TagIntArray final : Tag {
 public:
  explicit TagIntArray(std::vector<int32_t> data)
      : TagIntArray("", std::move(data)) {}
  TagIntArray(icu::UnicodeString name, std::vector<int32_t> data)
      : Tag(TagType::IntArray, std::move(name)), m_data(std::move(data)) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  std::vector<int32_t> m_data;
};
}  // namespace celerity::nbt::tag

#endif
