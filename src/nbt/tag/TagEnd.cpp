#include "TagEnd.h"

void TagEnd::write(ByteBuffer &buffer, bool include_preamble) {
    write_type(buffer);
}

icu::UnicodeString TagEnd::to_string(uint8_t indent) {
    return "";
}
