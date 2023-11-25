#ifndef MCCPP_TAG_H
#define MCCPP_TAG_H

#include <cstdint>
#include <utility>
#include "../../ByteBuffer.h"
#include "TagType.h"

class Tag {
public:
    Tag(TagType type, std::wstring name) : m_type(std::move(type)), m_name(std::move(name)) {}

    [[nodiscard]] TagType get_type();
    [[nodiscard]] std::wstring get_name();
    void write_type(ByteBuffer &buffer);
    void write_name(ByteBuffer &buffer);
    void write(ByteBuffer &buffer);
    virtual void write(ByteBuffer &buffer, bool include_preamble) = 0;
private:
    TagType m_type;
    std::wstring m_name;
};

#endif
