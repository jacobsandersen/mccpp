#ifndef MCCPP_TAGFLOAT_H
#define MCCPP_TAGFLOAT_H

#include "Tag.h"

class TagFloat : public Tag {
public:
    TagFloat(icu::UnicodeString name, float value) : Tag(TagType::Float, std::move(name)), m_value(value) {}

    static TagFloat read(ByteBuffer &buffer);
    static TagFloat read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] float get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    float m_value;
};


#endif //MCCPP_TAGFLOAT_H
