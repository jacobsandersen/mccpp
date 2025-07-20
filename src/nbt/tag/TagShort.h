//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGSHORT_H
#define TAGSHORT_H

#include "Tag.h"

class TagShort final : public Tag {
public:
    explicit TagShort(const int16_t value) : TagShort("", value) {}
    TagShort(icu::UnicodeString name, const int16_t value) : Tag(TagType::Short, std::move(name)), m_value(value) {};
    void write_payload(ByteBuffer& buffer) const override;
private:
    int16_t m_value;
};

#endif //TAGSHORT_H
