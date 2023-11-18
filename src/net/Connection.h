#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <asio.hpp>

class MinecraftServer;

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
    MinecraftServer *server;

    Connection(asio::io_context& context, MinecraftServer *server) : socket(context), state(ConnectionState::Handshaking), server(server) {}

    [[nodiscard]] MinecraftServer *get_minecraft_server() const;
};

#endif
