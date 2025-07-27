//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGCOMPOUNDBUILDER_H
#define TAGCOMPOUNDBUILDER_H

#include "Concepts.h"
#include "tag/TagCompound.h"

namespace celerity::nbt {
class TagCompoundBuilder
    : public std::enable_shared_from_this<TagCompoundBuilder> {
 public:
  static std::shared_ptr<TagCompoundBuilder> create() { return create(""); }

  static std::shared_ptr<TagCompoundBuilder> create(icu::UnicodeString name);

  template <typename T>
    requires DerivedTag<T> && (!IsTagEnd<T>)
  std::shared_ptr<TagCompoundBuilder> add(T item) {
    m_compound.add(item);
    return shared_from_this();
  }

  tag::TagCompound build();

 private:
  TagCompoundBuilder() : TagCompoundBuilder("") {}
  explicit TagCompoundBuilder(icu::UnicodeString name)
      : m_compound(std::move(name)) {}
  tag::TagCompound m_compound;
};
}  // namespace celerity::nbt

#endif  // TAGCOMPOUNDBUILDER_H
