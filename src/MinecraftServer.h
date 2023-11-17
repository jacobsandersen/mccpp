//
// Created by simple on 11/9/23.
//

#ifndef MCCPP_MINECRAFTSERVER_H
#define MCCPP_MINECRAFTSERVER_H

#include <asio.hpp>
#include "net/Connection.h"

#define MINECRAFT_PORT 25565

using asio::ip::tcp;

class MinecraftServer {
public:
    asio::io_context& get_context();

    int get_players();
    void set_players(int players);
    int get_max_players();

    MinecraftServer(asio::io_context& context, int max_players) :
            m_context(context),
            m_acceptor(context, tcp::endpoint(tcp::v4(), MINECRAFT_PORT)),
            m_max_players(max_players) {
        MinecraftServer::start_accept();
    }
private:
    asio::io_context& m_context;
    tcp::acceptor m_acceptor;
    int m_players{};
    int m_max_players;

    void start_accept();
    void start_read(const std::shared_ptr<Connection>& conn);
};

#endif
