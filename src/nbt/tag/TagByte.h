#ifndef MCCPP_TAGBYTE_H
#define MCCPP_TAGBYTE_H


#include <utility>

#include "Tag.h"

class TagByte : public Tag {
public:
    explicit TagByte(int8_t value) : TagByte(L"", value) {}
    TagByte(std::wstring name, int8_t value) : Tag(TagType::Byte, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int8_t get_value() const;
private:
    int8_t m_value;
};


#endif //MCCPP_TAGBYTE_H
