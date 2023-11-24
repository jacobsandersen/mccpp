#ifndef MCCPP_TAGEND_H
#define MCCPP_TAGEND_H


#include "Tag.h"

class TagEnd : public Tag {
public:
    TagEnd() : Tag(TagType::End, L"") {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
};


#endif //MCCPP_TAGEND_H
