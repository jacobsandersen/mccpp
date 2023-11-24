#ifndef MCCPP_TAGLIST_H
#define MCCPP_TAGLIST_H

#include <utility>
#include <list>

#include "Tag.h"

class TagList : public Tag {
public:
    TagList(TagType list_type, std::list<std::shared_ptr<Tag>> items) : TagList(L"", std::move(list_type), std::move(items)) {}
    TagList(std::wstring name, TagType list_type, std::list<std::shared_ptr<Tag>> items) :
        Tag(TagType::List, std::move(name)),
        m_list_type(std::move(list_type)),
        m_items(std::move(items)) {
        for (auto& item : m_items) {
            if (item->get_type().get_type_id() != m_list_type.get_type_id()) {
                throw std::invalid_argument("Tried to create TagList with items of multiple tag types.");
            }
        }
    }

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] TagType get_list_type() const;
    [[nodiscard]] std::list<std::shared_ptr<Tag>> get_items() const;
private:
    TagType m_list_type;
    std::list<std::shared_ptr<Tag>> m_items;
};


#endif //MCCPP_TAGLIST_H
