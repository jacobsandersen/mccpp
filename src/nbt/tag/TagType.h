#ifndef MCCPP_TAGTYPE_H
#define MCCPP_TAGTYPE_H

#include <cstdint>
#include <string>
#include <utility>
#include <stdexcept>
#include <unordered_map>
#include <unicode/unistr.h>

class TagType {
public:
    static const TagType End;
    static const TagType Byte;
    static const TagType Short;
    static const TagType Int;
    static const TagType Long;
    static const TagType Float;
    static const TagType Double;
    static const TagType ByteArray;
    static const TagType String;
    static const TagType List;
    static const TagType Compound;
    static const TagType IntArray;
    static const TagType LongArray;
    static const TagType Types[13];

    static TagType type_id_to_type(uint8_t tag_type_id);
    static TagType expected_tag_type(int64_t integral_value);
    static TagType expected_tag_type(double fp_value);

    [[nodiscard]] uint8_t get_type_id() const;
    [[nodiscard]] icu::UnicodeString get_type_name() const;

    bool operator==(const TagType& rhs) const;
    bool operator!=(const TagType& rhs) const;
private:
    TagType(uint8_t type_id, icu::UnicodeString name) : m_type_id(type_id), m_name(std::move(name)) {}

    uint8_t m_type_id;
    icu::UnicodeString m_name;
};


#endif //MCCPP_TAGTYPE_H
