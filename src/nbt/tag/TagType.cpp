#include <limits>
#include "TagType.h"

#define MIN_INT8 (-128)
#define MAX_INT8 127
#define MIN_INT16 (-32768)
#define MAX_INT16 32767
#define MIN_INT32 (-2147483648)
#define MAX_INT32 2147483647

const TagType TagType::End = TagType(0, "TAG_End");
const TagType TagType::Byte = TagType(1, "TAG_Byte");
const TagType TagType::Short = TagType(2, "TAG_Short");
const TagType TagType::Int = TagType(3, "TAG_Int");
const TagType TagType::Long = TagType(4, "TAG_Long");
const TagType TagType::Float = TagType(5, "TAG_Float");
const TagType TagType::Double = TagType(6, "TAG_Double");
const TagType TagType::ByteArray = TagType(7, "TAG_ByteArray");
const TagType TagType::String = TagType(8, "TAG_String");
const TagType TagType::List = TagType(9, "TAG_List");
const TagType TagType::Compound = TagType(10, "TAG_Compound");
const TagType TagType::IntArray = TagType(11, "TAG_IntArray");
const TagType TagType::LongArray = TagType(12, "TAG_LongArray");

const TagType TagType::Types[13] = {End, Byte, Short, Int, Long, Float, Double,
                                    ByteArray, String, List, Compound, IntArray, LongArray};

uint8_t TagType::get_type_id() const {
    return m_type_id;
}

icu::UnicodeString TagType::get_type_name() const {
    return m_name;
}

bool TagType::operator==(const TagType &rhs) const {
    return m_type_id == rhs.m_type_id;
}

bool TagType::operator!=(const TagType &rhs) const {
    return !operator==(rhs);
}

TagType TagType::type_id_to_type(uint8_t tag_type_id) {
    if (tag_type_id > 12) {
        throw std::invalid_argument("Tried to get Tag Type with Tag Type ID > 12.");
    }

    return Types[tag_type_id];
}

TagType TagType::expected_tag_type(int64_t integral_value) {
    if (integral_value >= MIN_INT8 && integral_value <= MAX_INT8) {
        return TagType::Byte;
    } else if (integral_value >= MIN_INT16 && integral_value <= MAX_INT16) {
        return TagType::Short;
    } else if (integral_value >= MIN_INT32 && integral_value <= MAX_INT32) {
        return TagType::Int;
    } else {
        return TagType::Long;
    }
}

TagType TagType::expected_tag_type(double fp_value) {
    if (std::abs(fp_value - static_cast<float>(fp_value)) < std::numeric_limits<double>::epsilon()) {
        // the double value minus its float representation (with precision loss) is less than the actual double epsilon,
        // so the original number albeit being in a double is probably a float
        return TagType::Float;
    } else {
        return TagType::Double;
    }
}
