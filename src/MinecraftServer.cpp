#include "MinecraftServer.h"

#include <glog/logging.h>

#include "VarInt.h"

namespace celerity {
MinecraftServer* instance = nullptr;

MinecraftServer* MinecraftServer::get_server() {
  if (!instance) {
    instance = new MinecraftServer();
  }

  return instance;
}

void MinecraftServer::start() {
  LOG(INFO) << "Starting MCCPP...";
  m_network_manager.start();
  LOG(INFO) << "MCCPP stopping...";
}

std::vector<std::shared_ptr<player::Player>> MinecraftServer::get_players() {
  return m_players;
}

std::shared_ptr<player::Player> MinecraftServer::get_player(
    const std::string& username) {
  for (std::shared_ptr<player::Player> player : get_players()) {
    if (player->get_username() == username) {
      return player;
    }
  }

  return nullptr;
}

std::shared_ptr<player::Player> MinecraftServer::get_player(
    const std::shared_ptr<uuids::uuid>& unique_id) {
  for (std::shared_ptr<player::Player> player : get_players()) {
    if (player->get_unique_id() == unique_id) {
      return player;
    }
  }

  return nullptr;
}

void MinecraftServer::remove_player(
    const std::shared_ptr<uuids::uuid>& unique_id) {
  if (unique_id == nullptr) return;
  m_players.erase(
      std::remove_if(m_players.begin(), m_players.end(),
                     [unique_id](std::shared_ptr<player::Player> player) {
                       return player->get_unique_id() == unique_id;
                     }),
      m_players.end());
}

const net::NetworkManager& MinecraftServer::get_network_manager() const {
  return m_network_manager;
}

const RSAKeypair& MinecraftServer::get_rsa_keypair() const {
  return m_rsa_keypair;
}

void MinecraftServer::add_player(
    const std::shared_ptr<player::Player>& player) {
  m_players.push_back(player);
}

const ConfigManager& MinecraftServer::get_config_manager() const {
  return m_config_manager;
}

uint32_t MinecraftServer::get_protocol_version() const {
  return m_protocol_version;
}

const std::string& MinecraftServer::get_version_name() const {
  return m_version_name;
}

const std::vector<KnownPack>& MinecraftServer::get_known_packs() const {
  return m_known_packs;
}
}  // namespace celerity