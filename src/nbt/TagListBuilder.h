//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGLISTBUILDER_H
#define TAGLISTBUILDER_H

#include "tag/Tag.h"
#include "tag/TagList.h"
#include "util/Concepts.h"

template <typename T> requires DerivedTag<T> && (!IsTagEnd<T>)
class TagListBuilder : public std::enable_shared_from_this<TagListBuilder<T>> {
public:
    static std::shared_ptr<TagListBuilder> create()
    {
        return create("");
    }
    static std::shared_ptr<TagListBuilder> create(icu::UnicodeString name)
    {
        return std::make_shared<TagListBuilder>(name);
    }

    std::shared_ptr<TagListBuilder> add(T item)
    {
        m_list.add(item);
        return this->shared_from_this();
    }

    TagList<T> build()
    {
        return std::move(m_list);
    }
private:
    TagListBuilder() : TagListBuilder("") {}
    explicit TagListBuilder(icu::UnicodeString name) : m_list(std::move(name)) {}
    TagList<T> m_list;
};

#endif //TAGLISTBUILDER_H
