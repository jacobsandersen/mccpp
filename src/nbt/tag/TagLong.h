//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGLONG_H
#define TAGLONG_H
#include "Tag.h"

class TagLong final : public Tag {
public:
    explicit TagLong(const int64_t value) : TagLong("", value) {}
    TagLong(icu::UnicodeString name, const int64_t value) : Tag(TagType::Long, std::move(name)), m_value(value) {}
    void write_payload(ByteBuffer& buffer) const override;
private:
    int64_t m_value;
};

#endif //TAGLONG_H
