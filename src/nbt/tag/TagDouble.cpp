#include <iostream>
#include "TagDouble.h"

TagDouble TagDouble::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagDouble TagDouble::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    double value = buffer.read_be_double();
    return {name, value};
}

void TagDouble::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_double(m_value);
}

double TagDouble::get_value() const {
    return m_value;
}

static std::string stringified_dbl_max_precision(double value) {
    std::ostringstream os;
    os.precision(std::numeric_limits<double>::digits10);
    os << std::fixed << value;
    return std::move(os).str();
}

icu::UnicodeString TagDouble::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(stringified_dbl_max_precision(get_value())));
}
