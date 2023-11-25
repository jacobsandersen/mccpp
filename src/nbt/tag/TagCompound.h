#ifndef MCCPP_TAGCOMPOUND_H
#define MCCPP_TAGCOMPOUND_H

#include <list>
#include <utility>

#include "Tag.h"

class TagCompound : public Tag {
public:
    TagCompound(icu::UnicodeString name, std::list<std::shared_ptr<Tag>> items) : Tag(TagType::Compound, std::move(name)), m_items(std::move(items)) {}

    static TagCompound read(ByteBuffer &buffer);
    static TagCompound read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<std::shared_ptr<Tag>> get_items() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    std::list<std::shared_ptr<Tag>> m_items;
};


#endif //MCCPP_TAGCOMPOUND_H
