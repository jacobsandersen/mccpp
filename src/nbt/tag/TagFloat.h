#ifndef MCCPP_TAGFLOAT_H
#define MCCPP_TAGFLOAT_H

#include "Tag.h"

class TagFloat : public Tag {
public:
    explicit TagFloat(float value) : TagFloat(L"", value) {}
    TagFloat(std::wstring name, float value) : Tag(TagType::Float, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] float get_value() const;

private:
    float m_value;
};


#endif //MCCPP_TAGFLOAT_H
