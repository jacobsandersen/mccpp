//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAG_H
#define TAG_H

#include <utility>

#include "../../ByteBuffer.h"
#include "TagType.h"

namespace celerity::nbt::tag {
class Tag {
 public:
  explicit Tag(TagType type) : Tag(std::move(type), "") {};

  Tag(TagType type, icu::UnicodeString name)
      : m_type(std::move(type)), m_name(std::move(name)) {};

  virtual ~Tag() = default;

  void write(ByteBuffer& buffer) const { return write(buffer, true); }

  void write(ByteBuffer& buffer, const bool include_name) const {
    buffer.write_ubyte(m_type.get_type_id());
    if (include_name) buffer.write_string_modified_utf8(m_name);
    write_payload(buffer);
  }

  virtual void write_payload(ByteBuffer& buffer) const = 0;

  [[nodiscard]] TagType get_type() const { return m_type; }

  [[nodiscard]] icu::UnicodeString get_name() const { return m_name; }

 private:
  TagType m_type;
  icu::UnicodeString m_name;
};
}  // namespace celerity::nbt::tag

#endif  // TAG_H
