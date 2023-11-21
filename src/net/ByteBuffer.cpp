#include <glog/logging.h>
#include <stdexcept>
#include <cstring>
#include <utility>
#include <zlib.h>
#include "ByteBuffer.h"
#include "../VarInt.h"

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, void>::type
ByteBuffer::write_buffer(std::deque<uint8_t> &buffer, T value) {
    buffer.insert(
            buffer.end(),
            reinterpret_cast<uint8_t *>(&value),
            reinterpret_cast<uint8_t *>(&value) + sizeof(T));
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, void>::type
ByteBuffer::write_buffer(std::deque<uint8_t> &buffer, T value, uint32_t offset) {
    size_t size = sizeof(T);
    offset = offset * size;

    if (buffer.size() < offset + size) {
        buffer.resize(offset + size);
    }

    std::memcpy(&buffer[offset], reinterpret_cast<uint8_t *>(&value), size);

}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
static read_or_peek_buffer(std::deque<uint8_t> &buffer, uint32_t offset, bool erase) {
    size_t size = sizeof(T);
    offset = offset * size;

    if (buffer.empty() || buffer.size() < offset + size) {
        throw std::runtime_error("Buffer too small");
    }

    T value;
    std::memcpy(&value, &buffer[offset], size);

    if (erase) buffer.erase(buffer.begin() + offset, buffer.begin() + offset + static_cast<std::ptrdiff_t>(size));

    return value;
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
ByteBuffer::read_buffer(std::deque<uint8_t> &buffer, uint32_t offset) {
    return read_or_peek_buffer<T>(buffer, offset, true);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
ByteBuffer::read_buffer(std::deque<uint8_t> &buffer) {
    return read_buffer<T>(buffer, 0);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
ByteBuffer::peek_buffer(std::deque<uint8_t> &buffer, uint32_t offset) {
    return read_or_peek_buffer<T>(buffer, offset, false);
}

template<typename T>
typename std::enable_if<std::is_integral<T>::value || std::is_floating_point<T>::value, T>::type
ByteBuffer::peek_buffer(std::deque<uint8_t> &buffer) {
    return peek_buffer<T>(buffer, 0);
}

void ByteBuffer::write_boolean(bool value) {
    write_byte(value ? 0x1 : 0x0);
}

bool ByteBuffer::read_boolean() {
    return read_byte() == 0x1;
}

void ByteBuffer::write_byte(int8_t value) {
    write_buffer(m_data, value);
}

int8_t ByteBuffer::read_byte() {
    return read_buffer<int8_t>(m_data);
}

int8_t ByteBuffer::peek_byte() {
    return peek_byte(0);
}

int8_t ByteBuffer::peek_byte(uint32_t offset) {
    return peek_buffer<int8_t>(m_data, offset);
}

void ByteBuffer::write_bytes(const std::vector<int8_t> &bytes) {
    for (int8_t byte: bytes) {
        write_byte(byte);
    }
}

void ByteBuffer::write_bytes(const int8_t *bytes, size_t num_bytes) {
    for (int i = 0; i < num_bytes; i++) {
        write_byte(bytes[i]);
    }
}

std::vector<int8_t> ByteBuffer::read_bytes(size_t num_bytes) {
    std::vector<int8_t> vec;

    for (int i = 0; i < num_bytes; i++) {
        vec.push_back(read_byte());
    }

    return vec;
}

void ByteBuffer::write_ubyte(uint8_t value) {
    write_buffer(m_data, value);
}

void ByteBuffer::write_ubyte(uint8_t value, uint32_t offset) {
    write_buffer(m_data, value, offset);
}

uint8_t ByteBuffer::read_ubyte() {
    return read_buffer<uint8_t>(m_data);
}

uint8_t ByteBuffer::peek_ubyte() {
    return peek_ubyte(0);
}

uint8_t ByteBuffer::peek_ubyte(uint32_t offset) {
    return peek_buffer<uint8_t>(m_data, offset);
}

void ByteBuffer::write_ubytes(const std::vector<uint8_t> &ubytes) {
    for (uint8_t ubyte: ubytes) {
        write_ubyte(ubyte);
    }
}

void ByteBuffer::write_ubytes(const uint8_t *bytes, size_t num_bytes) {
    for (int i = 0; i < num_bytes; i++) {
        write_ubyte(bytes[i]);
    }
}

std::vector<uint8_t> ByteBuffer::read_ubytes(size_t num_ubytes) {
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

uint64_t ByteBuffer::read_ulong() {
    return read_buffer<uint64_t>(m_data);
}

void ByteBuffer::write_ulong(uint64_t value) {
    write_buffer(m_data, value);
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

void ByteBuffer::write_string(const std::string &str) {
    write_varint(static_cast<int32_t>(str.length()));
    for (int8_t byte: str) {
        write_byte(byte);
    }
}

void ByteBuffer::write_string(const std::string &str, uint16_t length) {
    if (str.length() > length) {
        throw std::invalid_argument("write_string string length greater than enforced length");
    }

    write_varint(static_cast<int32_t>(length));

    uint16_t bytes_written = 0;
    for (int8_t byte: str) {
        write_byte(byte);
        bytes_written++;
    }

    if (str.length() < length) {
        uint16_t remainingLength = length - str.length();
        for (int i = 0; i < remainingLength; i++) {
            write_byte(0); // padding byte
        }
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

std::string ByteBuffer::read_string(uint16_t length) {
    std::string s = read_string();

    if (s.length() < length) {
        for (int i = 0; i < length - s.length(); i++) {
            read_byte(); // padding byte
        }
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

uuids::uuid ByteBuffer::read_uuid() {
    uint64_t most_significant = read_ulong();
    uint64_t least_significant = read_ulong();
    std::array<uuids::uuid::value_type, 16> uuid_bytes{};
    std::memcpy(uuid_bytes.data(), &most_significant, sizeof(uint64_t));
    std::memcpy(uuid_bytes.data() + 8, &least_significant, sizeof(uint64_t));
    return {uuid_bytes};
}

void ByteBuffer::write_uuid(uuids::uuid unique_id) {
    auto bytes = unique_id.as_bytes();
    uint64_t most_significant, least_significant;
    std::memcpy(&most_significant, bytes.data(), sizeof(uint64_t));
    std::memcpy(&least_significant, bytes.data() + 8, sizeof(uint64_t));
    write_ulong(most_significant);
    write_ulong(least_significant);
}

void ByteBuffer::append(const ByteBuffer& buffer) {
    for (auto byte : buffer.get_data()) {
        m_data.insert(m_data.end(), byte);
    }
}

std::deque<uint8_t> ByteBuffer::get_data() const {
    return m_data;
}

void ByteBuffer::set_data(std::deque<uint8_t> data) {
    m_data = std::move(data);
}

uint32_t ByteBuffer::get_data_length() const {
    return m_data.size();
}

#define COMPRESSION_CHUNK 4096

int ByteBuffer::compress_buffer() {
    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
        return -1;
    }

    std::vector<uint8_t> input_bytes = std::vector(m_data.begin(), m_data.end());

    stream.next_in = input_bytes.data();
    stream.avail_in = input_bytes.size();

    std::vector<uint8_t> output_bytes(input_bytes.size());
    do {
        stream.next_out = output_bytes.data() + stream.total_out;
        stream.avail_out = output_bytes.size() - stream.total_out;

        if (deflate(&stream, Z_FINISH) == Z_STREAM_ERROR) {
            deflateEnd(&stream);
            return -1;
        }

        // shouldn't happen but just to be safe
        if (stream.avail_out == 0) {
            output_bytes.resize(output_bytes.size() * 2);
        }
    } while (stream.avail_in > 0);

    deflateEnd(&stream);
    output_bytes.resize(stream.total_out);

    m_data.clear();

    for (uint8_t byte : output_bytes) {
        m_data.push_back(byte);
    }

    return 0;
}

int ByteBuffer::decompress_buffer() {
    LOG(INFO) << "Decompressing buffer...";

    z_stream stream;
    stream.zalloc = Z_NULL;
    stream.zfree = Z_NULL;
    stream.opaque = Z_NULL;

    if (inflateInit(&stream) != Z_OK) {
        LOG(WARNING) << "Inflate initialization failed";
        return -1;
    }

    std::vector<uint8_t> input_bytes = std::vector(m_data.begin(), m_data.end());

    stream.next_in = input_bytes.data();
    stream.avail_in = input_bytes.size();

    LOG(INFO) << "Set up the next_in and avail_in variables";

    std::vector<uint8_t> output_bytes(input_bytes.size() * 2);
    do {
        LOG(INFO) << " Iterating. Setting next_out and avail_out.";

        stream.next_out = output_bytes.data() + stream.total_out;
        stream.avail_out = output_bytes.capacity() - stream.total_out;

        LOG(INFO) << " Inflating...";
        if (inflate(&stream, Z_NO_FLUSH) == Z_STREAM_ERROR) {
            LOG(WARNING) << "Inflate failed. Stopping decompression.";
            inflateEnd(&stream);
            return -1;
        }

        if (stream.avail_out == 0) {
            output_bytes.resize(output_bytes.size() * 2);
        }
    } while (stream.avail_in > 0);

    LOG(INFO) << "Done decompressing. Total out = " << stream.total_out;

    inflateEnd(&stream);
    output_bytes.resize(stream.total_out);

    LOG(INFO) << "Replacing bytes in buffer...";

    m_data.clear();

    for (uint8_t byte : output_bytes) {
        m_data.push_back(byte);
    }

    LOG(INFO) << "Done decompressing.";

    return 0;
}



