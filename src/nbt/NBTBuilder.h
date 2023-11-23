#ifndef MCCPP_NBTBUILDER_H
#define MCCPP_NBTBUILDER_H

#include <utility>

#include "../net/ByteBuffer.h"
#include "NBTTag.h"

using std::shared_ptr, std::make_shared;

namespace NBT {
    template <typename T> using is_tag = std::is_base_of<Tag<typename std::decay_t<T>::type>, typename std::decay_t<T>::type>;
    template <typename T> using is_no_param_tag = std::disjunction<std::is_same<TagCompound, typename std::decay_t<T>::type>, std::is_same<TagEnd, typename std::decay_t<T>::type>>;
    template <typename T> using is_param_tag = std::conjunction<is_tag<std::decay_t<T>>, std::negation<is_no_param_tag<std::decay_t<T>>>>;

    class NBTBuilder : public std::enable_shared_from_this<NBTBuilder> {
    public:
        static shared_ptr<NBTBuilder> create() {
            return shared_ptr<NBTBuilder>(new NBTBuilder());
        }

        shared_ptr<NBTBuilder> add_tag_end() {
            if (m_open_tags == 0) {
                throw std::runtime_error("Tried to add TAG_End, but no TAG_Compounds are open.");
            }

            m_open_tags--;

            TagEnd end;
            end.write(m_buffer);
        }

        shared_ptr<NBTBuilder> add_tag_compound(std::string name) {
            TagCompound t(std::move(name));
            t.write(m_buffer);
            m_open_tags++;
            return shared_from_this();
        }

        // only defined if T is a Tag that takes parameters (i.e., not TagCompound, not TagEnd)
        template <typename T, typename ValueType = std::enable_if_t<is_param_tag<T>::value>> std::shared_ptr<NBTBuilder> add(std::string name, ValueType value) {
            T t(std::move(name), value);
            t.write(m_buffer);
            return shared_from_this();
        }

        // only defined if T is a TagList holding ValueType, and ValueType is a Tag.
        template <typename T, typename ValueType, typename = std::enable_if_t<std::conjunction_v<std::is_same<TagList<ValueType>, T>, is_tag<ValueType>>, T>> std::shared_ptr<NBTBuilder> add(std::string name, std::vector<ValueType> value) {
            TagList<ValueType> t(std::move(name), std::move(value));
            t.write(m_buffer);
            return shared_from_this();
        }

        ByteBuffer build() {
            return m_buffer;
        }
    private:
        NBTBuilder() : m_buffer(), m_open_tags(0) {}

        ByteBuffer m_buffer;
        uint32_t m_open_tags;
    };
}

#endif
