#ifndef MCCPP_TAGLONGARRAY_H
#define MCCPP_TAGLONGARRAY_H

#include <list>
#include <utility>

#include "Tag.h"

class TagLongArray : public Tag {
public:
    TagLongArray(icu::UnicodeString name, std::list<int64_t> value) : Tag(TagType::LongArray, std::move(name)), m_value(std::move(value)) {}

    static TagLongArray read(ByteBuffer &buffer);
    static TagLongArray read(ByteBuffer &buffer, bool include_name);
    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int64_t> get_value() const;
    icu::UnicodeString to_string(uint8_t indent) override;
private:
    std::list<int64_t> m_value;
};


#endif //MCCPP_TAGLONGARRAY_H
