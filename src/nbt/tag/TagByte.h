//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGBYTE_H
#define TAGBYTE_H

#include "Tag.h"

class TagByte final : public Tag {
public:
    explicit TagByte(const int8_t byte) : TagByte("", byte) {}
    TagByte(icu::UnicodeString name, const int8_t byte) : Tag(TagType::Byte, std::move(name)), m_byte(byte) {}
    void write_payload(ByteBuffer& buffer) const override;
private:
    int8_t m_byte;
};



#endif //TAGBYTE_H
