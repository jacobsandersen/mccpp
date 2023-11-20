#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <asio.hpp>
#include <uuid.h>
#include <deque>
#include <cryptopp/modes.h>

#define VERIFY_TOKEN_SIZE 4
#define SHARED_SECRET_SIZE 16

enum class ConnectionState {
    Handshaking,
    Status,
    Login,
    Configuration,
    Play
};

class Connection {
public:
    explicit Connection(asio::io_context& context) : m_socket(context) {}

    [[nodiscard]] asio::ip::tcp::socket *get_socket();

    [[nodiscard]] asio::streambuf *get_buffer();

    [[nodiscard]] ConnectionState get_state() const;

    void set_state(ConnectionState state);

    [[nodiscard]] const std::vector<uint8_t> &get_verify_token() const;

    void set_verify_token(const std::vector<uint8_t> &verifyToken);

    [[nodiscard]] const std::vector<uint8_t> &get_shared_secret() const;

    void set_shared_secret(const std::vector<uint8_t> &sharedSecret);

    [[nodiscard]] bool get_encrypt_packets() const;

    void enable_encryption();

    [[nodiscard]] const std::shared_ptr<uuids::uuid> &get_unique_id() const;

    void set_unique_id(const std::shared_ptr<uuids::uuid> &unique_id);

    std::deque<uint8_t> encrypt_bytes(std::deque<uint8_t> bytes);
private:
    asio::ip::tcp::socket m_socket;
    asio::streambuf m_buffer{};
    ConnectionState m_state = ConnectionState::Handshaking;
    std::vector<uint8_t> m_verify_token{};
    std::vector<uint8_t> m_shared_secret{};
    bool m_encrypt_packets{};
    std::shared_ptr<uuids::uuid> m_unique_id{};
    CryptoPP::CFB_Mode_ExternalCipher::Encryption m_cfb_stream_cipher{};
};

#endif
