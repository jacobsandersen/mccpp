#include "TagFloat.h"

TagFloat TagFloat::read(ByteBuffer &buffer) {
    return read(buffer, true);
}

TagFloat TagFloat::read(ByteBuffer &buffer, bool include_name) {
    icu::UnicodeString name = include_name ? buffer.read_string_modified_utf8() : "";
    float value = buffer.read_be_float();
    return {name, value};
}

void TagFloat::write(ByteBuffer &buffer, bool include_preamble) {
    Tag::write(buffer, include_preamble);
    buffer.write_be_float(m_value);
}

float TagFloat::get_value() const {
    return m_value;
}

static std::string stringified_flt_max_precision(float value) {
    std::ostringstream os;
    os.precision(std::numeric_limits<float>::digits10);
    os << std::fixed << value;
    return std::move(os).str();
}

icu::UnicodeString TagFloat::to_string(uint8_t indent) {
    return icu::UnicodeString(Tag::to_string(indent) + " " + icu::UnicodeString::fromUTF8(stringified_flt_max_precision(get_value())));
}
