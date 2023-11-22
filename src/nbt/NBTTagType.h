#ifndef MCCPP_NBTTAGTYPE_H
#define MCCPP_NBTTAGTYPE_H

#include <cstdint>
#include <string>
#include <utility>
#include <typeinfo>
#include <vector>

namespace NBT {
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

        [[nodiscard]] uint8_t get_value() const;
        [[nodiscard]] std::string get_name() const;
    private:
        TagType(uint8_t value, std::string name) : m_value(value), m_name(std::move(name)) {}

        uint8_t m_value;
        std::string m_name;
    };
}

#endif //MCCPP_NBTTAGTYPE_H
