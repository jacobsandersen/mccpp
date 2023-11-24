#ifndef MCCPP_TAGCOMPOUND_H
#define MCCPP_TAGCOMPOUND_H

#include <list>
#include <utility>

#include "Tag.h"

class TagCompound : public Tag {
public:
    explicit TagCompound(std::list<std::shared_ptr<Tag>> items) : TagCompound(L"", std::move(items)) {}
    TagCompound(std::wstring name, std::list<std::shared_ptr<Tag>> items) : Tag(TagType::Compound, std::move(name)), m_items(std::move(items)) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<std::shared_ptr<Tag>> get_items() const;
private:
    std::list<std::shared_ptr<Tag>> m_items;
};


#endif //MCCPP_TAGCOMPOUND_H
