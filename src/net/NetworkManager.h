#ifndef MCCPP_NETWORKMANAGER_H
#define MCCPP_NETWORKMANAGER_H

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include "Connection.h"

#define MINECRAFT_PORT 25565

class NetworkManager {
public:
    NetworkManager() :
            m_context(),
            m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), MINECRAFT_PORT)) {}

    void start();

private:
    asio::io_context m_context;
    asio::ip::tcp::acceptor m_acceptor;

    void start_accept();

    void start_read(const std::shared_ptr<Connection> &conn);
};


#endif
