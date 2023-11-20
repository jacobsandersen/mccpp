//
// Created by simple on 11/13/23.
//

#ifndef MCCPP_BYTEBUFFER_H
#define MCCPP_BYTEBUFFER_H

#include <cstdint>
#include <deque>
#include <vector>
#include <uuid.h>
#include "Connection.h"

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

    void write_ushort(uint16_t);

    uint16_t read_ushort();

    void write_int(int32_t);

    int32_t read_int();

    void write_uint(uint32_t);

    uint32_t read_uint();

    void write_long(int64_t);

    int64_t read_long();

    uint64_t read_ulong();

    void write_ulong(uint64_t);

    void write_float(float);

    float read_float();

    void write_double(double);

    double read_double();

    void write_string(const std::string &);

    void write_string(const std::string &, uint16_t);

    std::string read_string();

    std::string read_string(uint16_t length);

    void write_varint(int32_t);

    int32_t read_varint();

    void write_varlong(int64_t);

    int64_t read_varlong();

    uuids::uuid read_uuid();

    void write_uuid(uuids::uuid unique_id);

    [[nodiscard]] std::deque<uint8_t> get_data() const;

    [[nodiscard]] uint32_t get_data_length() const;

    void encrypt_buffer(const std::shared_ptr<Connection> &);

    void decrypt_buffer(const std::shared_ptr<Connection> &);

private:
    std::deque<uint8_t> m_data;
};


#endif
