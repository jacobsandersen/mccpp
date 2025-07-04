#ifndef MCCPP_MINECRAFTSERVER_H
#define MCCPP_MINECRAFTSERVER_H

#include <boost/asio.hpp>
#include <cryptopp/rsa.h>
#include <toml.hpp>
#include "net/Connection.h"
#include "player/Player.h"
#include "net/NetworkManager.h"
#include "RSAKeypair.h"
#include "ConfigManager.h"

using boost::asio::ip::tcp;

class MinecraftServer {
public:
    static MinecraftServer *get_server();

    void start();

    [[nodiscard]] const NetworkManager &get_network_manager() const;

    [[nodiscard]] const ConfigManager &get_config_manager() const;

    [[nodiscard]] const RSAKeypair &get_rsa_keypair() const;

    const std::string &get_version_name() const;

    [[nodiscard]] uint32_t get_protocol_version() const;

    std::vector<std::shared_ptr<Player>> get_players();

    std::shared_ptr<Player> get_player(const std::string &username);

    std::shared_ptr<Player> get_player(const std::shared_ptr<uuids::uuid> &unique_id);

    void remove_player(const std::shared_ptr<uuids::uuid> &unique_id);

    void add_player(const std::shared_ptr<Player> &);

private:
    MinecraftServer()
            : m_network_manager(), m_config_manager(), m_rsa_keypair(), m_version_name("1.21.7"),
              m_protocol_version(772) {}

    NetworkManager m_network_manager;
    ConfigManager m_config_manager;
    RSAKeypair m_rsa_keypair;
    std::string m_version_name;
    uint32_t m_protocol_version;

    std::vector<std::shared_ptr<Player>> m_players{};
};

#endif
