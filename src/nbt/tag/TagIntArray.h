#ifndef MCCPP_TAGINTARRAY_H
#define MCCPP_TAGINTARRAY_H

#include <list>
#include <utility>

#include "Tag.h"

class TagIntArray : public Tag {
public:
    explicit TagIntArray(std::list<int32_t> value) : TagIntArray(L"", value) {}
    TagIntArray(std::wstring name, std::list<int32_t> value) : Tag(TagType::IntArray, std::move(name)), m_value(std::move(value)) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int32_t> get_value() const;
private:
    std::list<int32_t> m_value;
};


#endif //MCCPP_TAGINTARRAY_H
