//
// Created by simple on 11/9/23.
//

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

struct Connection {
    asio::ip::tcp::socket socket;
    asio::streambuf buffer{};
    ConnectionState state;

    explicit Connection(asio::io_context& context) : socket(context), state(ConnectionState::Handshaking) {}
};

#endif //MCCPP_CONNECTION_H
