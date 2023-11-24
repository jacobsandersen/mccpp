#ifndef MCCPP_TAGSTRING_H
#define MCCPP_TAGSTRING_H

#include <utility>

#include "Tag.h"

class TagString : public Tag {
public:
    explicit TagString(std::wstring value) : TagString(L"", std::move(value)) {}
    TagString(std::wstring name, std::wstring value) : Tag(TagType::String, std::move(name)), m_value(std::move(value)) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] std::wstring get_value() const;

private:
    std::wstring m_value;
};


#endif //MCCPP_TAGSTRING_H
