#ifndef MCCPP_TAGEND_H
#define MCCPP_TAGEND_H


#include "Tag.h"

class TagEnd : public Tag {
public:
    TagEnd() : Tag(TagType::End, "") {}

    void write(ByteBuffer &buffer, bool include_preamble) override;
    icu::UnicodeString to_string(uint8_t indent) override;
};


#endif //MCCPP_TAGEND_H
