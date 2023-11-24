#ifndef MCCPP_TAGINT_H
#define MCCPP_TAGINT_H

#include "Tag.h"

class TagInt : public Tag {
public:
    explicit TagInt(int32_t value) : TagInt(L"", value) {}
    TagInt(std::wstring name, int32_t value) : Tag(TagType::Int, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int32_t get_value() const;
private:
    int32_t m_value;
};


#endif //MCCPP_TAGINT_H
