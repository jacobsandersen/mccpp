//
// Created by Jacob Andersen on 7/19/25.
//

#ifndef TAGLONGARRAY_H
#define TAGLONGARRAY_H
#include "Tag.h"

class TagLongArray final : public Tag {
public:
    explicit TagLongArray(std::vector<int64_t> data) : TagLongArray("", std::move(data)) {}
    TagLongArray(icu::UnicodeString name, std::vector<int64_t> data) : Tag(TagType::LongArray, std::move(name)), m_data(std::move(data)) {}
    void write_payload(ByteBuffer& buffer) const override;
private:
    std::vector<int64_t> m_data;
};

#endif //TAGLONGARRAY_H
