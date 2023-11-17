//
// Created by simple on 11/9/23.
//

#ifndef MCCPP_MINECRAFTSERVER_H
#define MCCPP_MINECRAFTSERVER_H

#include <asio.hpp>
#include <cryptopp/rsa.h>
#include "net/Connection.h"

#define MINECRAFT_PORT 25565

using asio::ip::tcp;

class MinecraftServer {
public:
    int get_players();
    void set_players(int players);
    int get_max_players();

    MinecraftServer(int max_players, CryptoPP::RSA::PublicKey& public_key, CryptoPP::RSA::PrivateKey& private_key) :
            m_context(),
            m_acceptor(m_context, tcp::endpoint(tcp::v4(), MINECRAFT_PORT)),
            m_max_players(max_players),
            m_public_key(public_key),
            m_private_key(private_key) {}

    void start();
private:
    asio::io_context m_context;
    tcp::acceptor m_acceptor;
    int m_players{};
    int m_max_players;
    CryptoPP::RSA::PublicKey& m_public_key;
    CryptoPP::RSA::PrivateKey& m_private_key;

    void start_accept();
    void start_read(const std::shared_ptr<Connection>& conn);
};

#endif
