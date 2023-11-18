#include <iostream>
#include <cryptopp/osrng.h>
#include "MinecraftServer.h"
#include "VarInt.h"
#include "net/PacketHandler.h"

void MinecraftServer::start() {
    std::cout << "Generating RSA keypair. Please wait...";
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, 1024);
    auto privateKey = new CryptoPP::RSA::PrivateKey(params);
    auto publicKey = new CryptoPP::RSA::PublicKey(*privateKey);
    std::cout << "Keypair generated." << std::endl;

    m_rsa_pub_key = publicKey;
    m_rsa_priv_key = privateKey;

    MinecraftServer::start_accept();
    m_context.run();
}

void MinecraftServer::start_accept() {
    auto conn = std::make_shared<Connection>(m_context, this);
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

CryptoPP::RSA::PublicKey *MinecraftServer::getRSAPublicKey() const {
    return m_rsa_pub_key;
}

CryptoPP::RSA::PrivateKey *MinecraftServer::getRSAPrivateKey() const {
    return m_rsa_priv_key;
}


