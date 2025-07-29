//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CELERITY_NBT_CONCEPTS_H
#define CELERITY_NBT_CONCEPTS_H

#include "tag/TagEnd.h"

namespace celerity::nbt {
template <typename T>
concept DerivedTag = std::derived_from<T, tag::Tag>;

template <typename T>
concept IsTagEnd = std::is_same_v<T, tag::TagEnd>;
}  // namespace celerity::nbt

#endif
