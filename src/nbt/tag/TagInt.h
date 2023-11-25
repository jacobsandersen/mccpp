#ifndef MCCPP_TAGINT_H
#define MCCPP_TAGINT_H

#include "Tag.h"

class TagInt : public Tag {
public:
    TagInt(icu::UnicodeString name, int32_t value) : Tag(TagType::Int, std::move(name)), m_value(value) {}

    static TagInt read(ByteBuffer &buffer);
    static TagInt read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int32_t get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    int32_t m_value;
};


#endif //MCCPP_TAGINT_H
