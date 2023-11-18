#include <iostream>
#include <cryptopp/osrng.h>
#include "MinecraftServer.h"
#include "VarInt.h"
#include "net/PacketHandler.h"

MinecraftServer *instance = nullptr;

MinecraftServer *MinecraftServer::get_server() {
    if (!instance) {
        instance = new MinecraftServer();
    }

    return instance;
}

void MinecraftServer::start() {
    m_network_manager.start();
}

std::vector<std::shared_ptr<Player>> MinecraftServer::get_players() {
    return m_players;
}

std::shared_ptr<Player> MinecraftServer::get_player(const std::string& username) {
    for (std::shared_ptr<Player> player : get_players()) {
        if (player->getUsername() == username) {
            return player;
        }
    }

    return nullptr;
}

std::shared_ptr<Player> MinecraftServer::get_player(uuids::uuid unique_id) {
    for (std::shared_ptr<Player> player : get_players()) {
        if (*player->getUniqueId() == unique_id) {
            return player;
        }
    }

    return nullptr;
}

const NetworkManager &MinecraftServer::get_network_manager() const {
    return m_network_manager;
}

const RSAKeypair &MinecraftServer::get_rsa_keypair() const {
    return m_rsa_keypair;
}

void MinecraftServer::add_player(const std::shared_ptr<Player>& player) {
    m_players.push_back(player);
}






