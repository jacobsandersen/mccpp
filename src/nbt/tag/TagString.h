#ifndef MCCPP_TAGSTRING_H
#define MCCPP_TAGSTRING_H

#include <utility>

#include "Tag.h"

class TagString : public Tag {
public:
    TagString(icu::UnicodeString name, icu::UnicodeString value) : Tag(TagType::String, std::move(name)), m_value(std::move(value)) {}

    static TagString read(ByteBuffer &buffer);
    static TagString read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] icu::UnicodeString get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    icu::UnicodeString m_value;
};


#endif //MCCPP_TAGSTRING_H
