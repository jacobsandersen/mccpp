#ifndef MCCPP_TAGBYTEARRAY_H
#define MCCPP_TAGBYTEARRAY_H

#include <list>
#include <utility>
#include "Tag.h"

class TagByteArray : public Tag {
public:
    TagByteArray(icu::UnicodeString name, std::list<int8_t> value) : Tag(TagType::ByteArray, std::move(name)), m_value(std::move(value)) {}

    static TagByteArray read(ByteBuffer &buffer);
    static TagByteArray read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int8_t> get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    std::list<int8_t> m_value;
};


#endif //MCCPP_TAGBYTEARRAY_H
