#ifndef CELERITY_MINECRAFTSERVER_H
#define CELERITY_MINECRAFTSERVER_H

#include <boost/asio.hpp>

#include "ConfigManager.h"
#include "RSAKeypair.h"
#include "net/Connection.h"
#include "net/NetworkManager.h"
#include "player/Player.h"

using boost::asio::ip::tcp;

namespace celerity {
class MinecraftServer {
 public:
  static MinecraftServer* get_server();

  void start();

  [[nodiscard]] const net::NetworkManager& get_network_manager() const;

  [[nodiscard]] const ConfigManager& get_config_manager() const;

  [[nodiscard]] const RSAKeypair& get_rsa_keypair() const;

  const std::string& get_version_name() const;

  [[nodiscard]] uint32_t get_protocol_version() const;

  std::vector<std::shared_ptr<player::Player>> get_players();

  std::shared_ptr<player::Player> get_player(const std::string& username);

  std::shared_ptr<player::Player> get_player(
      const std::shared_ptr<uuids::uuid>& unique_id);

  void remove_player(const std::shared_ptr<uuids::uuid>& unique_id);

  void add_player(const std::shared_ptr<player::Player>&);

  const std::vector<KnownPack>& get_known_packs() const;

 private:
  MinecraftServer() : m_version_name("1.21.7"), m_protocol_version(772) {
    m_known_packs.emplace_back("minecraft", "core", "1.21.5");
  }

  net::NetworkManager m_network_manager;
  ConfigManager m_config_manager;
  RSAKeypair m_rsa_keypair;
  std::string m_version_name;
  uint32_t m_protocol_version;
  std::vector<KnownPack> m_known_packs;

  std::vector<std::shared_ptr<player::Player>> m_players{};
};
}  // namespace celerity
#endif
