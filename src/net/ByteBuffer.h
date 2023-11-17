//
// Created by simple on 11/13/23.
//

#ifndef MCCPP_BYTEBUFFER_H
#define MCCPP_BYTEBUFFER_H

#include <cstdint>
#include <deque>
#include <vector>

class ByteBuffer {
public:
    ByteBuffer() : m_data(std::deque<uint8_t>()) {}

    void write_boolean(bool);
    bool read_boolean();
    void write_byte(int8_t);
    int8_t read_byte();
    void write_bytes(const std::vector<int8_t>&);
    void write_bytes(const int8_t*, size_t);
    std::vector<int8_t> read_bytes(uint8_t);
    void write_ubyte(uint8_t);
    uint8_t read_ubyte();
    void write_ubytes(const std::vector<uint8_t>&);
    void write_ubytes(const uint8_t*, size_t);
    std::vector<uint8_t> read_ubytes(uint8_t);
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
    void write_float(float);
    float read_float();
    void write_double(double);
    double read_double();
    void write_string(const std::string&);
    std::string read_string();
    void write_varint(int32_t);
    int32_t read_varint();
    void write_varlong(int64_t);
    int64_t read_varlong();
    [[nodiscard]] std::deque<uint8_t> get_data() const;
    [[nodiscard]] uint32_t get_data_length() const;
private:
    std::deque<uint8_t> m_data;
};


#endif
