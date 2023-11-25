#ifndef MCCPP_TAGDOUBLE_H
#define MCCPP_TAGDOUBLE_H


#include "Tag.h"

class TagDouble : public Tag {
public:
    TagDouble(icu::UnicodeString name, double value) : Tag(TagType::Double, std::move(name)), m_value(value) {}

    static TagDouble read(ByteBuffer &buffer);
    static TagDouble read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] double get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    double m_value;
};


#endif //MCCPP_TAGDOUBLE_H
