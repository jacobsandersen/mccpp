#ifndef MCCPP_NBTTAG_H
#define MCCPP_NBTTAG_H

#include <type_traits>
#include <utility>
#include "NBTTagType.h"
#include "../ByteBuffer.h"

namespace NBT {
    template <typename T> class Tag {
    public:
        [[nodiscard]] TagType get_type() const;
        [[nodiscard]] std::string get_name() const;
        [[nodiscard]] T get_value() const;
    protected:
        Tag(TagType type, std::string name, T value) : m_type(std::move(type)), m_name(std::move(name)), m_value(std::move(value)) {}
        virtual void write(ByteBuffer& buffer) = 0;
    private:
        TagType m_type;
        std::string m_name;
        T m_value;
    };

    class TagEnd : public Tag<std::nullptr_t > {
    public:
        TagEnd() : Tag<std::nullptr_t>(TagType::End, "", nullptr) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagByte : public Tag<int8_t> {
    public:
        TagByte(std::string name, int8_t value) : Tag<int8_t>(TagType::Byte, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagShort : public Tag<int16_t> {
    public:
        TagShort(std::string name, int16_t value) : Tag<int16_t>(TagType::Short, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagInt : public Tag<int32_t> {
    public:
        explicit TagInt(std::string name, int32_t value) : Tag<int32_t>(TagType::Int, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagLong : public Tag<int64_t> {
    public:
        TagLong(std::string name, int64_t value) : Tag<int64_t>(TagType::Long, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagFloat : public Tag<float> {
    public:
        TagFloat(std::string name, float value) : Tag<float>(TagType::Float, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagDouble : public Tag<double> {
    public:
        TagDouble(std::string name, double value) : Tag<double>(TagType::Double, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagByteArray : public Tag<std::vector<int8_t>> {
    public:
        TagByteArray(std::string name, std::vector<int8_t> value) : Tag<std::vector<int8_t>>(TagType::ByteArray, std::move(name), std::move(value)) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagString : public Tag<std::string> {
    public:
        TagString(std::string name, std::string value) : Tag<std::string>(TagType::String, std::move(name), std::move(value)) {}

        void write(ByteBuffer &buffer) override;
    };

    template <typename T, typename = std::enable_if<std::is_base_of_v<Tag<T>, T>>> class TagList : public Tag<std::vector<T>> {
    public:
        TagList(std::string name, std::vector<T> value) : Tag<std::vector<T>>(TagType::List, std::move(name), value) {}

        void write(ByteBuffer &buffer) override;
    };


    class TagCompound : public Tag<std::nullptr_t> {
    public:
        explicit TagCompound(std::string name) : Tag<nullptr_t>(TagType::Compound, std::move(name), nullptr) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagIntArray : public Tag<std::vector<int32_t>> {
    public:
        explicit TagIntArray(std::string name, std::vector<int32_t> value) : Tag<std::vector<int32_t>>(TagType::IntArray, std::move(name), std::move(value)) {}

        void write(ByteBuffer &buffer) override;
    };

    class TagLongArray : public Tag<std::vector<int64_t>> {
    public:
        explicit TagLongArray(std::string name, std::vector<int64_t> value) : Tag<std::vector<int64_t>>(TagType::LongArray, std::move(name), std::move(value)) {}

        void write(ByteBuffer &buffer) override;
    };
}

#endif
