#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <asio.hpp>

enum class ConnectionState {
    Handshaking,
    Status,
    Login,
    Configuration,
    Play
};

class Connection {
public:
    explicit Connection(asio::io_context& context) :
            m_socket(context),
            m_state(ConnectionState::Handshaking) {}

    [[nodiscard]] asio::ip::tcp::socket *get_socket();

    [[nodiscard]] asio::streambuf *get_buffer();

    [[nodiscard]] ConnectionState get_state() const;

    void set_state(ConnectionState state);
private:
    asio::ip::tcp::socket m_socket;
    asio::streambuf m_buffer{};
    ConnectionState m_state;
};

#endif
