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
    std::cout << "Starting minecraft server" << std::endl;
    std::thread([this](){
        m_network_manager.start();
    }).detach();
    std::cout << "Server started" << std::endl;
    while (true) {}
}

std::vector<std::shared_ptr<Player>> MinecraftServer::get_players() {
    return m_players;
}

std::shared_ptr<Player> MinecraftServer::get_player(const std::string& username) {
    for (std::shared_ptr<Player> player : get_players()) {
        if (player->get_username() == username) {
            return player;
        }
    }

    return nullptr;
}

std::shared_ptr<Player> MinecraftServer::get_player(const std::shared_ptr<uuids::uuid>& unique_id) {
    for (std::shared_ptr<Player> player : get_players()) {
        if (player->get_unique_id() == unique_id) {
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

const ConfigManager &MinecraftServer::get_config_manager() const {
    return m_config_manager;
}

uint32_t MinecraftServer::get_protocol_version() const {
    return m_protocol_version;
}

const std::string &MinecraftServer::get_version_name() const {
    return m_version_name;
}







