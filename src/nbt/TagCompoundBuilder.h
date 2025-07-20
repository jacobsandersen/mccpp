//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGCOMPOUNDBUILDER_H
#define TAGCOMPOUNDBUILDER_H

#include "tag/TagCompound.h"
#include "tag/TagString.h"
#include "util/Concepts.h"

class TagCompoundBuilder : public std::enable_shared_from_this<TagCompoundBuilder>{
public:
    static std::shared_ptr<TagCompoundBuilder> create()
    {
        return create("");
    }

    static std::shared_ptr<TagCompoundBuilder> create(icu::UnicodeString name);

    template <typename T> requires DerivedTag<T> && (!IsTagEnd<T>) std::shared_ptr<TagCompoundBuilder> add(T item)
    {
        m_compound.add(item);
        return shared_from_this();
    }

    TagCompound build();
private:
    TagCompoundBuilder() : TagCompoundBuilder("") {}
    explicit TagCompoundBuilder(icu::UnicodeString name) : m_compound(std::move(name)) {}
    TagCompound m_compound;
};

#endif //TAGCOMPOUNDBUILDER_H
