#ifndef MCCPP_TAGSHORT_H
#define MCCPP_TAGSHORT_H


#include "Tag.h"

class TagShort : public Tag {
public:
    TagShort(icu::UnicodeString name, int16_t value) : Tag(TagType::Short, std::move(name)), m_value(value) {}

    static TagShort read(ByteBuffer &buffer);
    static TagShort read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int16_t get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    int16_t m_value;
};


#endif //MCCPP_TAGSHORT_H
