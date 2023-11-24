#ifndef MCCPP_TAGDOUBLE_H
#define MCCPP_TAGDOUBLE_H


#include "Tag.h"

class TagDouble : public Tag {
public:
    explicit TagDouble(double value) : TagDouble(L"", value) {}
    TagDouble(std::wstring name, double value) : Tag(TagType::Double, std::move(name)), m_value(value) {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    [[nodiscard]] double get_value() const;

private:
    double m_value;
};


#endif //MCCPP_TAGDOUBLE_H
