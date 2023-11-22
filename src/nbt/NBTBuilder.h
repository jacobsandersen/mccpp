#ifndef MCCPP_NBTBUILDER_H
#define MCCPP_NBTBUILDER_H

#include <utility>

#include "../net/ByteBuffer.h"
#include "NBTTag.h"

using std::shared_ptr, std::make_shared;

namespace NBT {
    class NBTBuilder : public std::enable_shared_from_this<NBTBuilder> {
    public:
        static shared_ptr<NBTBuilder> create() {
            return shared_ptr<NBTBuilder>(new NBTBuilder());
        }

        shared_ptr<NBTBuilder> add_tag_end() {
            if (open_tags == 0) {
                throw std::runtime_error("Tried to add TAG_End, but no TAG_Compounds are open.");
            }

            open_tags--;

            TagEnd end;
            end.write(m_buffer);
        }

        shared_ptr<NBTBuilder> add_tag_byte(std::string name, int8_t value) {
            TagByte t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_short(std::string name, int16_t value) {
            TagShort t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_int(std::string name, int32_t value) {
            TagInt t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_long(std::string name, int64_t value) {
            TagLong t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_float(std::string name, float value) {
            TagFloat t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_double(std::string name, double value) {
            TagDouble t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_byte_array(std::string name, std::vector<int8_t> value) {
            TagByteArray t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_string(std::string name, std::string value) {
            TagString t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        template <typename T, typename = std::enable_if<std::is_base_of_v<Tag<T>, T>>> shared_ptr<NBTBuilder> add_tag_list(std::string name, std::vector<T> value) {
            TagList<T> t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_compound(std::string name) {
            TagCompound t(std::move(name));
            t.write(m_buffer);
            open_tags++;
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_int_array(std::string name, std::vector<int32_t> value) {
            TagIntArray t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        shared_ptr<NBTBuilder> add_tag_long_array(std::string name, std::vector<int64_t> value) {
            TagLongArray t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        ByteBuffer build() {
            return m_buffer;
        }
    private:
        NBTBuilder() : m_buffer(), open_tags(0) {}

        ByteBuffer m_buffer;
        uint32_t open_tags;
    };
}

#endif
