#include "TagType.h"

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
