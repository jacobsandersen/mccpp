#include <stdexcept>
#include <cstring>
#include <utility>
#include "ByteBuffer.h"
#include "../VarInt.h"

template <typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, void>::type
static write_buffer(std::deque<uint8_t>& buffer, T value) {
    buffer.insert(
            buffer.end(),
            reinterpret_cast<uint8_t*>(&value),
            reinterpret_cast<uint8_t*>(&value) + sizeof(T));
}

template <typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
static read_buffer(std::deque<uint8_t>& buffer) {
    size_t size = sizeof(T);

    if (buffer.empty() || buffer.size() < size) {
        throw std::runtime_error("Buffer too small");
    }

    T value;
    std::memcpy(&value, &buffer[0], size);

    buffer.erase(buffer.begin(), buffer.begin() + static_cast<std::ptrdiff_t>(size));

    return value;
}


void ByteBuffer::write_boolean(bool value) {
    write_buffer(m_data, value ? 0x01 : 0x00);
}

bool ByteBuffer::read_boolean() {
    return read_byte() == 0x01;
}

void ByteBuffer::write_byte(int8_t value) {
    write_buffer(m_data, value);
}

int8_t ByteBuffer::read_byte() {
    return read_buffer<int8_t>(m_data);
}

void ByteBuffer::write_bytes(const std::vector<int8_t>& bytes) {
    for (int8_t byte : bytes) {
        write_byte(byte);
    }
}

void ByteBuffer::write_bytes(const int8_t *bytes, size_t num_bytes) {
    for (int i = 0; i < num_bytes; i++) {
        write_byte(*(bytes + 1));
    }
}

std::vector<int8_t> ByteBuffer::read_bytes(uint8_t num_bytes) {
    std::vector<int8_t> vec;

    for (int i = 0; i < num_bytes; i++) {
        vec.push_back(read_byte());
    }

    return vec;
}

void ByteBuffer::write_ubyte(uint8_t value) {
    write_buffer(m_data, value);
}

uint8_t ByteBuffer::read_ubyte() {
    return read_buffer<uint8_t>(m_data);
}

void ByteBuffer::write_ubytes(const std::vector<uint8_t>& ubytes) {
    for (uint8_t ubyte : ubytes) {
        write_ubyte(ubyte);
    }
}

void ByteBuffer::write_ubytes(const uint8_t *bytes, size_t num_bytes) {
    for (int i = 0; i < num_bytes; i++) {
        write_ubyte(*(bytes + 1));
    }
}

std::vector<uint8_t> ByteBuffer::read_ubytes(uint8_t num_ubytes) {
    std::vector<uint8_t> vec;

    for (int i = 0; i < num_ubytes; i++) {
        vec.push_back(read_ubyte());
    }

    return vec;
}

void ByteBuffer::write_short(int16_t value) {
    write_buffer(m_data, value);
}

int16_t ByteBuffer::read_short() {
    return read_buffer<int16_t>(m_data);
}

void ByteBuffer::write_ushort(uint16_t value) {
    write_buffer(m_data, value);
}

uint16_t ByteBuffer::read_ushort() {
    return read_buffer<uint16_t>(m_data);
}

void ByteBuffer::write_int(int32_t value) {
    write_buffer(m_data, value);
}

int32_t ByteBuffer::read_int() {
    return read_buffer<int32_t>(m_data);
}

void ByteBuffer::write_uint(uint32_t value) {
    write_buffer(m_data, value);
}

uint32_t ByteBuffer::read_uint() {
    return read_buffer<uint32_t>(m_data);
}

void ByteBuffer::write_long(int64_t value) {
    write_buffer(m_data, value);
}

int64_t ByteBuffer::read_long() {
    return read_buffer<int64_t>(m_data);
}

void ByteBuffer::write_float(float value) {
    write_buffer(m_data, value);
}

float ByteBuffer::read_float() {
    return read_buffer<float>(m_data);
}

void ByteBuffer::write_double(double value) {
    write_buffer(m_data, value);
}

double ByteBuffer::read_double() {
    return read_buffer<double>(m_data);
}

void ByteBuffer::write_string(const std::string& str) {
    write_varint(static_cast<int32_t>(str.length()));
    for (int8_t byte : str) {
        write_byte(byte);
    }
}

std::string ByteBuffer::read_string() {
    int32_t length = read_varint();
    std::string s;

    for (int i = 0; i < length; i++) {
        s.push_back(read_byte());
    }

    return s;
}

void ByteBuffer::write_varint(int32_t value) {
    auto *encoded = new int8_t[5];
    uint8_t bytes_written;

    VarInt::encode_varint(value, encoded, &bytes_written);

    for (int i = 0; i < bytes_written; i++) {
        write_byte(encoded[i]);
    }
}

int32_t ByteBuffer::read_varint() {
    return VarInt::decode_varint(this, nullptr);
}

void ByteBuffer::write_varlong(int64_t value) {
    int8_t *encoded;
    uint8_t bytes_written;

    VarInt::encode_varlong(value, encoded, &bytes_written);

    for (int i = 0; i < bytes_written; i++) {
        write_byte(encoded[i]);
    }
}

int64_t ByteBuffer::read_varlong() {
    return VarInt::decode_varlong(this, nullptr);
}

std::deque<uint8_t> ByteBuffer::get_data() const {
    return m_data;
}

uint32_t ByteBuffer::get_data_length() const {
    return m_data.size();
}
