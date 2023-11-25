#ifndef MCCPP_TAGLONG_H
#define MCCPP_TAGLONG_H

#include "Tag.h"

class TagLong : public Tag {
public:
    TagLong(icu::UnicodeString name, int64_t value) : Tag(TagType::Long, std::move(name)), m_value(value) {}

    static TagLong read(ByteBuffer &buffer);
    static TagLong read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int64_t get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    int64_t m_value;
};


#endif //MCCPP_TAGLONG_H
