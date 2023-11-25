#ifndef MCCPP_TAG_H
#define MCCPP_TAG_H

#include <cstdint>
#include <utility>
#include <unicode/unistr.h>
#include <unicode/msgfmt.h>
#include "../../ByteBuffer.h"
#include "TagType.h"

class Tag {
public:
    Tag(TagType type, icu::UnicodeString name) : m_type(std::move(type)), m_name(std::move(name)) {}

    [[nodiscard]] TagType get_type();
    [[nodiscard]] icu::UnicodeString get_name();
    void write_type(ByteBuffer &buffer);
    void write_name(ByteBuffer &buffer);
    void write(ByteBuffer &buffer);
    virtual void write(ByteBuffer &buffer, bool include_preamble) = 0;
    virtual icu::UnicodeString to_string(uint8_t indent) = 0;
private:
    TagType m_type;
    icu::UnicodeString m_name;
};

#endif
