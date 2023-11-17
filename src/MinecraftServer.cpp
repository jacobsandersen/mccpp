#include <iostream>
#include "MinecraftServer.h"
#include "VarInt.h"
#include "net/PacketHandler.h"

int MinecraftServer::get_players() {
    return m_players;
}

void MinecraftServer::set_players(int players) {
    m_players = players;
}

int MinecraftServer::get_max_players() {
    return m_max_players;
}

void MinecraftServer::start_accept() {
    auto conn = std::make_shared<Connection>(m_context);
    m_acceptor.async_accept(conn->socket, [this, conn](const asio::error_code &err) {
        if (!err) {
            std::cout << "start_accept: connection established from remote endpoint "
                      << conn->socket.remote_endpoint().address().to_string() << std::endl;

            std::thread([this, conn]() {
                MinecraftServer::start_read(conn);
            }).detach();

            MinecraftServer::start_accept();
        } else {
            std::cerr << "start_accept: failed to accept new connection: " << err.message() << std::endl;
        }
    });
}

void MinecraftServer::start_read(const std::shared_ptr<Connection> &conn) {
    asio::async_read(
            conn->socket,
            conn->buffer,
            asio::transfer_at_least(1),
            [this, conn](const asio::error_code &err, size_t bytes_transferred) {
                if (!err) {
                    PacketHandler::handle_packet(conn, &bytes_transferred);
                    MinecraftServer::start_read(conn);
                }
            });
}


