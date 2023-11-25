//
// Created by simple on 11/13/23.
//

#ifndef MCCPP_BYTEBUFFER_H
#define MCCPP_BYTEBUFFER_H

#include <cstdint>
#include <deque>
#include <vector>
#include <uuid.h>
#include <unicode/unistr.h>
#include "nbt/tag/TagType.h"

class ByteBuffer {
public:
    ByteBuffer() : m_data(std::deque<uint8_t>()) {}

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, void>::type
    write_buffer(std::deque<uint8_t> &buffer, T value);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, void>::type
    write_buffer(std::deque<uint8_t> &buffer, T value, uint32_t offset);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
    read_buffer(std::deque<uint8_t> &buffer, uint32_t offset);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
    read_buffer(std::deque<uint8_t> &buffer);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
    peek_buffer(std::deque<uint8_t> &buffer, uint32_t offset);

    template<typename T>
    typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
    peek_buffer(std::deque<uint8_t> &buffer);

    void write_boolean(bool);

    bool read_boolean();

    void write_byte(int8_t);

    int8_t read_byte();

    int8_t peek_byte();

    int8_t peek_byte(uint32_t index);

    void write_bytes(const std::vector<int8_t> &);

    void write_bytes(const int8_t *, size_t);

    std::vector<int8_t> read_bytes(size_t);

    void write_ubyte(uint8_t);

    void write_ubyte(uint8_t, uint32_t);

    uint8_t read_ubyte();

    uint8_t peek_ubyte();

    uint8_t peek_ubyte(uint32_t index);

    void write_ubytes(const std::vector<uint8_t> &);

    void write_ubytes(const uint8_t *, size_t);

    std::vector<uint8_t> read_ubytes(size_t);

    void write_short(int16_t);

    int16_t read_short();

    void write_be_short(int16_t);

    int16_t read_be_short();

    void write_ushort(uint16_t);

    uint16_t read_ushort();

    void write_be_ushort(uint16_t);

    uint16_t read_be_ushort();

    void write_int(int32_t);

    int32_t read_int();

    void write_be_int(int32_t);

    int32_t read_be_int();

    void write_uint(uint32_t);

    uint32_t read_uint();

    void write_be_uint(uint32_t);

    uint32_t read_be_uint();

    void write_long(int64_t);

    int64_t read_long();

    void write_be_long(int64_t);

    int64_t read_be_long();

    void write_ulong(uint64_t);

    uint64_t read_ulong();

    void write_be_ulong(uint64_t);

    uint64_t read_be_ulong();

    void write_float(float);

    float read_float();

    void write_be_float(float);

    float read_be_float();

    void write_double(double);

    double read_double();

    void write_be_double(double);

    double read_be_double();

    void write_string(const std::string &);

    std::string read_string();

    void write_string_modified_utf8(const icu::UnicodeString &);

    icu::UnicodeString read_string_modified_utf8();

    void write_varint(int32_t);

    int32_t read_varint();

    void write_varlong(int64_t);

    int64_t read_varlong();

    TagType read_nbt_tag_type();

    uuids::uuid read_uuid();

    void write_uuid(uuids::uuid unique_id);

    void append(const ByteBuffer& buffer);

    [[nodiscard]] std::deque<uint8_t> get_data() const;

    void set_data(std::deque<uint8_t> data);

    [[nodiscard]] uint32_t get_data_length() const;

    int compress_buffer();

    int decompress_buffer();

private:
    std::deque<uint8_t> m_data;
};


#endif
