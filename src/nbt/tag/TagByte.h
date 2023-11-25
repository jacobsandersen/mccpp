#ifndef MCCPP_TAGBYTE_H
#define MCCPP_TAGBYTE_H

#include <utility>

#include "Tag.h"

class TagByte : public Tag {
public:
    TagByte(icu::UnicodeString name, int8_t value) : Tag(TagType::Byte, std::move(name)), m_value(value) {}

    static TagByte read(ByteBuffer &buffer);
    static TagByte read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int8_t get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    int8_t m_value;
};


#endif //MCCPP_TAGBYTE_H
