//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_TAG_TAGLONGARRAY_H
#define CELERITY_NBT_TAG_TAGLONGARRAY_H

#include "Tag.h"

namespace celerity::nbt::tag {
class TagLongArray final : public Tag {
 public:
  explicit TagLongArray(std::vector<int64_t> data)
      : TagLongArray("", std::move(data)) {}
  TagLongArray(icu::UnicodeString name, std::vector<int64_t> data)
      : Tag(TagType::LongArray, std::move(name)), m_data(std::move(data)) {}
  void write_payload(ByteBuffer& buffer) const override;

 private:
  std::vector<int64_t> m_data;
};
}  // namespace celerity::nbt::tag

#endif
