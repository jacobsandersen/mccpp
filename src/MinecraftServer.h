#ifndef MCCPP_MINECRAFTSERVER_H
#define MCCPP_MINECRAFTSERVER_H

#include <asio.hpp>
#include <cryptopp/rsa.h>
#include "net/Connection.h"
#include "player/Player.h"
#include "net/NetworkManager.h"
#include "RSAKeypair.h"

using asio::ip::tcp;

class MinecraftServer {
public:
    static MinecraftServer *get_server();

    void start();

    [[nodiscard]] const NetworkManager &get_network_manager() const;

    [[nodiscard]] const RSAKeypair &get_rsa_keypair() const;

    std::vector<std::shared_ptr<Player>> get_players();

    std::shared_ptr<Player> get_player(const std::string& username);

    std::shared_ptr<Player> get_player(const std::shared_ptr<uuids::uuid>& unique_id);

    void add_player(const std::shared_ptr<Player>&);
private:
    MinecraftServer() : m_network_manager(), m_rsa_keypair() {}

    NetworkManager m_network_manager;
    RSAKeypair m_rsa_keypair;

    std::vector<std::shared_ptr<Player>> m_players{};
};

#endif
