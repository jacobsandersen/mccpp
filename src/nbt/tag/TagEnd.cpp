#include "TagEnd.h"

void TagEnd::write(ByteBuffer &buffer, bool include_preamble) {
    write_type(buffer);
}
