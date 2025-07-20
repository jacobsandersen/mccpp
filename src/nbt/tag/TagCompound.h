//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGCOMPOUND_H
#define TAGCOMPOUND_H

#include "Tag.h"
#include "../util/Concepts.h"

class TagCompound final : public Tag {
public:
    TagCompound() : TagCompound("") {}
    explicit TagCompound(icu::UnicodeString name) : Tag(TagType::Compound, std::move(name)) {}

    template <typename T> requires DerivedTag<T> && (!IsTagEnd<T>) void add(T value)
    {
        m_internal_list.push_back(std::make_unique<T>(std::forward<T>(value)));
    }

    void write_payload(ByteBuffer& buffer) const override;
private:
    std::vector<std::unique_ptr<Tag>> m_internal_list;
};



#endif //TAGCOMPOUND_H
