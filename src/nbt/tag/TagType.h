#ifndef MCCPP_TAGTYPE_H
#define MCCPP_TAGTYPE_H

#include <cstdint>
#include <string>
#include <utility>

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

    [[nodiscard]] uint8_t get_type_id() const;
    [[nodiscard]] std::string get_type_name() const;

    bool operator==(const TagType& rhs) const;
    bool operator!=(const TagType& rhs) const;
private:
    TagType(uint8_t type_id, std::string name) : m_type_id(type_id), m_name(std::move(name)) {}

    uint8_t m_type_id;
    std::string m_name;
};


#endif //MCCPP_TAGTYPE_H
