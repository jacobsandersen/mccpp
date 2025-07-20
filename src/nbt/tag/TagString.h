//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGSTRING_H
#define TAGSTRING_H

#include "Tag.h"

class TagString final : public Tag {
public:
    explicit TagString(icu::UnicodeString value) : TagString("", std::move(value)) {}
    TagString(icu::UnicodeString name, icu::UnicodeString value) : Tag(TagType::String, std::move(name)), m_value(std::move(value)) {}
    void write_payload(ByteBuffer& buffer) const override;
private:
    icu::UnicodeString m_value;
};


#endif //TAGSTRING_H
