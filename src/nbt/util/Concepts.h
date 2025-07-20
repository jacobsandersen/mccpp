//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef CONCEPTS_H
#define CONCEPTS_H

#include "../tag/Tag.h"
#include "../tag/TagEnd.h"

template <typename T> concept DerivedTag = std::derived_from<T, Tag>;
template <typename T> concept IsTagEnd = std::is_same_v<T, TagEnd>;

#endif //CONCEPTS_H
