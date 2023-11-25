#include "Tag.h"

TagType Tag::get_type() {
    return m_type;
}

icu::UnicodeString Tag::get_name() {
    return m_name;
}

void Tag::write_type(ByteBuffer &buffer) {
    buffer.write_ubyte(m_type.get_type_id());
}

void Tag::write_name(ByteBuffer &buffer) {
    buffer.write_string_modified_utf8(m_name);
}

void Tag::write(ByteBuffer &buffer) {
    Tag::write(buffer, true);
}

void Tag::write(ByteBuffer &buffer, bool include_preamble) {
    if (include_preamble) {
        write_type(buffer);
        write_name(buffer);
    }
}

icu::UnicodeString Tag::to_string(uint8_t indent) {
    icu::UnicodeString indentation;
    for (int i = 0; i < indent; i++) indentation.append("\t");
    return icu::UnicodeString(indentation + m_type.get_type_name() + "(" + (m_name.isEmpty() ? "None" : "'" + get_name() + "'") + "):");
}
