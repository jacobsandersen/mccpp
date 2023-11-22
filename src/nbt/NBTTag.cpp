#include "NBTTag.h"

namespace NBT {
    template<typename T> TagType Tag<T>::get_type() const {
        return m_type;
    }

    template<typename T> std::string Tag<T>::get_name() const {
        return m_name;
    }

    template<typename T> T Tag<T>::get_value() const {
        return m_value;
    }

    void TagEnd::write(ByteBuffer &buffer) {

    }

    void TagByte::write(ByteBuffer &buffer) {

    }

    void TagShort::write(ByteBuffer &buffer) {

    }

    void TagInt::write(ByteBuffer &buffer) {

    }

    void TagLong::write(ByteBuffer &buffer) {

    }

    void TagFloat::write(ByteBuffer &buffer) {

    }

    void TagDouble::write(ByteBuffer &buffer) {

    }

    void TagByteArray::write(ByteBuffer &buffer) {

    }

    void TagString::write(ByteBuffer &buffer) {

    }

    template<typename T, typename Enable> void TagList<T, Enable>::write(ByteBuffer &buffer) {

    }

    void TagCompound::write(ByteBuffer &buffer) {

    }

    void TagIntArray::write(ByteBuffer &buffer) {

    }


    void TagLongArray::write(ByteBuffer &buffer) {

    }
}