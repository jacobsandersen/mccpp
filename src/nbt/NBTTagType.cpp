#include "NBTTagType.h"

namespace NBT {
    const TagType TagType::End = TagType(0, "TAG_End");
    const TagType TagType::Byte = TagType(1, "TAG_Byte");
    const TagType TagType::Short = TagType(2, "TAG_Short");
    const TagType TagType::Int = TagType(3, "TAG_Int");
    const TagType TagType::Long = TagType(4, "TAG_Long");
    const TagType TagType::Float = TagType(5, "TAG_Float");
    const TagType TagType::Double = TagType(6, "TAG_Double");
    const TagType TagType::ByteArray = TagType(7, "TAG_Byte_Array");
    const TagType TagType::String = TagType(8, "TAG_String");
    const TagType TagType::List = TagType(9, "TAG_List");
    const TagType TagType::Compound = TagType(10, "TAG_Compound");
    const TagType TagType::IntArray = TagType(11, "TAG_Int_Array");
    const TagType TagType::LongArray = TagType(12, "TAG_Long_Array");

    uint8_t TagType::get_value() const {
        return m_value;
    }

    std::string TagType::get_name() const {
        return m_name;
    }
}
