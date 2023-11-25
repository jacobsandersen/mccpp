#ifndef MCCPP_TAGINTARRAY_H
#define MCCPP_TAGINTARRAY_H

#include <list>
#include <utility>

#include "Tag.h"

class TagIntArray : public Tag {
public:
    TagIntArray(icu::UnicodeString name, std::list<int32_t> value) : Tag(TagType::IntArray, std::move(name)), m_value(std::move(value)) {}

    static TagIntArray read(ByteBuffer &buffer);
    static TagIntArray read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int32_t> get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    std::list<int32_t> m_value;
};


#endif //MCCPP_TAGINTARRAY_H
