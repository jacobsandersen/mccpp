#ifndef MCCPP_TAGLONGARRAY_H
#define MCCPP_TAGLONGARRAY_H

#include <list>
#include <utility>

#include "Tag.h"

class TagLongArray : public Tag {
public:
    explicit TagLongArray(std::list<int64_t> value) : TagLongArray(L"", std::move(value)) {}
    TagLongArray(std::wstring name, std::list<int64_t> value) : Tag(TagType::LongArray, std::move(name)), m_value(std::move(value)) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int64_t> get_value() const;
private:
    std::list<int64_t> m_value;
};


#endif //MCCPP_TAGLONGARRAY_H
