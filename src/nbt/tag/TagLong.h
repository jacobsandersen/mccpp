#ifndef MCCPP_TAGLONG_H
#define MCCPP_TAGLONG_H

#include "Tag.h"

class TagLong : public Tag {
public:
    explicit TagLong(int64_t value) : TagLong(L"", value) {}
    TagLong(std::wstring name, int64_t value) : Tag(TagType::Long, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] int64_t get_value() const;

private:
    int64_t m_value;
};


#endif //MCCPP_TAGLONG_H
