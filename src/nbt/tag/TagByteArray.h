#ifndef MCCPP_TAGBYTEARRAY_H
#define MCCPP_TAGBYTEARRAY_H

#include <list>
#include <utility>
#include "Tag.h"

class TagByteArray : public Tag {
public:
    explicit TagByteArray(std::list<int8_t> value) : TagByteArray(L"", std::move(value)) {}
    TagByteArray(std::wstring name, std::list<int8_t> value) : Tag(TagType::ByteArray, std::move(name)), m_value(std::move(value)) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::list<int8_t> get_value() const;
private:
    std::list<int8_t> m_value;
};


#endif //MCCPP_TAGBYTEARRAY_H
