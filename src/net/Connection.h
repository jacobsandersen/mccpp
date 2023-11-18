#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <asio.hpp>
#include <uuid.h>

#define VERIFY_TOKEN_SIZE 12
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

    [[nodiscard]] const std::shared_ptr<uuids::uuid> &get_unique_id() const;

    void set_unique_id(const std::shared_ptr<uuids::uuid> &unique_id);
private:
    asio::ip::tcp::socket m_socket;
    asio::streambuf m_buffer{};
    ConnectionState m_state = ConnectionState::Handshaking;
    std::vector<uint8_t> m_verify_token{};
    std::vector<uint8_t> m_shared_secret{};
    std::shared_ptr<uuids::uuid> m_unique_id{};
};

#endif
