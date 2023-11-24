#ifndef MCCPP_TAGSHORT_H
#define MCCPP_TAGSHORT_H


#include "Tag.h"

class TagShort : public Tag {
public:
    explicit TagShort(int16_t value) : TagShort(L"", value) {}
    TagShort(std::wstring name, int16_t value) : Tag(TagType::Short, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int16_t get_value() const;
private:
    int16_t m_value;
};


#endif //MCCPP_TAGSHORT_H
