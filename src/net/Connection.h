#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <asio.hpp>
#include <uuid.h>
#include <deque>
#include <cryptopp/modes.h>
#include "../ByteBuffer.h"

#define VERIFY_TOKEN_SIZE 4
#define SHARED_SECRET_SIZE 16

enum class ConnectionState {
    Handshaking,
    Status,
    Login,
    Configuration,
    Play
};

enum class BufferReadState {
    ReadPacketLength,
    ReadDataLength,
    DecompressData,
    ReadPacketId,
    HandlePacket
};

struct BufferReadContext {
    BufferReadState read_state = BufferReadState::ReadPacketLength;
    std::unique_ptr<ByteBuffer> partial_buffer = nullptr;
    std::unique_ptr<int32_t> packet_length = nullptr;
    std::unique_ptr<int32_t> data_length = nullptr;
    std::unique_ptr<int32_t> packet_id = nullptr;
};

class Connection {
public:
    explicit Connection(asio::io_context &context) : m_socket(context), m_read_context() {}

    [[nodiscard]] asio::ip::tcp::socket *get_socket();

    [[nodiscard]] ByteBuffer &get_data_buffer();

    [[nodiscard]] BufferReadContext &get_read_context();

    [[nodiscard]] ConnectionState get_state() const;

    void set_state(ConnectionState state);

    [[nodiscard]] const std::shared_ptr<uuids::uuid> &get_unique_id() const;

    void set_unique_id(const std::shared_ptr<uuids::uuid> &unique_id);

    [[nodiscard]] const std::vector<uint8_t> &get_verify_token() const;

    void set_verify_token(const std::vector<uint8_t> &verifyToken);

    [[nodiscard]] const std::vector<uint8_t> &get_shared_secret() const;

    void set_shared_secret(const std::vector<uint8_t> &sharedSecret);

    [[nodiscard]] bool get_compress_packets() const;

    void enable_compression();

    [[nodiscard]] bool get_encrypt_packets() const;

    void enable_encryption();

    std::deque<uint8_t> encrypt_bytes(std::deque<uint8_t>);

    std::deque<uint8_t> decrypt_bytes(std::deque<uint8_t>);
private:
    asio::ip::tcp::socket m_socket;
    ByteBuffer m_data_buffer{};
    BufferReadContext m_read_context{};
    ConnectionState m_state = ConnectionState::Handshaking;
    std::vector<uint8_t> m_verify_token{};
    std::vector<uint8_t> m_shared_secret{};
    bool m_compress_packets{};
    bool m_encrypt_packets{};
    std::shared_ptr<uuids::uuid> m_unique_id{};
    CryptoPP::CFB_Mode_ExternalCipher::Encryption m_cfb_stream_cipher_encryption{};
    CryptoPP::CFB_Mode_ExternalCipher::Decryption m_cfb_stream_cipher_decryption{};
};

#endif
