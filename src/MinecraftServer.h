#ifndef MCCPP_MINECRAFTSERVER_H
#define MCCPP_MINECRAFTSERVER_H

#include <asio.hpp>
#include <cryptopp/rsa.h>
#include "net/Connection.h"

#define MINECRAFT_PORT 25565

using asio::ip::tcp;

class MinecraftServer {
public:
    MinecraftServer() :
            m_context(),
            m_acceptor(m_context, tcp::endpoint(tcp::v4(), MINECRAFT_PORT)) {}

    void start();
    [[nodiscard]] CryptoPP::RSA::PublicKey *getRSAPublicKey() const;
    [[nodiscard]] CryptoPP::RSA::PrivateKey *getRSAPrivateKey() const;
private:
    asio::io_context m_context;
    tcp::acceptor m_acceptor;
    CryptoPP::RSA::PublicKey *m_rsa_pub_key{};
    CryptoPP::RSA::PrivateKey *m_rsa_priv_key{};

    void start_accept();
    void start_read(const std::shared_ptr<Connection>& conn);
};

#endif
