//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGBYTEARRAY_H
#define TAGBYTEARRAY_H
#include <utility>

#include "Tag.h"

class TagByteArray final : public Tag {
public:
    explicit TagByteArray(std::vector<int8_t> data) : TagByteArray("", std::move(data)) {}
    TagByteArray(icu::UnicodeString name, std::vector<int8_t> data) : Tag(TagType::ByteArray, std::move(name)), m_data(std::move(data)) {}
    void write_payload(ByteBuffer& buffer) const override;
private:
    std::vector<int8_t> m_data;
};

#endif //TAGBYTEARRAY_H
