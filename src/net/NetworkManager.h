#ifndef CELERITY_NET_NETWORKMANAGER_H
#define CELERITY_NET_NETWORKMANAGER_H

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "Connection.h"
#include "InboundPacket.h"
#include "configuration/in/PacketConfigurationInClientInformation.h"
#include "configuration/in/PacketConfigurationInKeepAlive.h"
#include "configuration/in/PacketConfigurationInKnownPacks.h"
#include "configuration/in/PacketConfigurationInPluginMessage.h"
#include "handshaking/in/PacketHandshakingInHandshake.h"
#include "login/in/PacketLoginInEncryptionResponse.h"
#include "login/in/PacketLoginInLoginAcknowledged.h"
#include "login/in/PacketLoginInLoginPluginResponse.h"
#include "login/in/PacketLoginInLoginStart.h"
#include "status/in/PacketStatusInPingRequest.h"
#include "status/in/PacketStatusInStatusRequest.h"

using std::unordered_map, std::unique_ptr, std::make_unique;

#define MINECRAFT_PORT 25565

namespace celerity::net {
class NetworkManager {
 public:
  NetworkManager()
      : m_context(),
        m_acceptor(m_context, boost::asio::ip::tcp::endpoint(
                                  boost::asio::ip::tcp::v4(), MINECRAFT_PORT)),
        m_packet_handlers() {
    // handshaking packets
    auto handshaking_handlers =
        make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
    handshaking_handlers->insert(
        {0x00, make_unique<handshaking::PacketHandshakingInHandshake>()});
    m_packet_handlers.insert(
        {ConnectionState::Handshaking, std::move(handshaking_handlers)});

    // status packets
    auto status_handlers =
        make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
    status_handlers->insert(
        {0x00, make_unique<status::PacketStatusInStatusRequest>()});
    status_handlers->insert(
        {0x01, make_unique<status::PacketStatusInPingRequest>()});
    m_packet_handlers.insert(
        {ConnectionState::Status, std::move(status_handlers)});

    // login packets
    auto login_handlers =
        make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
    login_handlers->insert(
        {0x00, make_unique<login::PacketLoginInLoginStart>()});
    login_handlers->insert(
        {0x01, make_unique<login::PacketLoginInEncryptionResponse>()});
    login_handlers->insert(
        {0x02, make_unique<login::PacketLoginInLoginPluginResponse>()});
    login_handlers->insert(
        {0x03, make_unique<login::PacketLoginInLoginAcknowledged>()});
    m_packet_handlers.insert(
        {ConnectionState::Login, std::move(login_handlers)});

    // configuration packets
    auto configuration_handlers =
        make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
    configuration_handlers->insert(
        {0x00,
         make_unique<configuration::PacketConfigurationInClientInformation>()});
    configuration_handlers->insert(
        {0x02,
         make_unique<configuration::PacketConfigurationInPluginMessage>()});
    configuration_handlers->insert(
        {0x04, make_unique<configuration::PacketConfigurationInKeepAlive>()});
    configuration_handlers->insert(
        {0x07, make_unique<configuration::PacketConfigurationInKnownPacks>()});
    m_packet_handlers.insert(
        {ConnectionState::Configuration, std::move(configuration_handlers)});

    // play packets
    auto play_handlers =
        make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
    m_packet_handlers.insert({ConnectionState::Play, std::move(play_handlers)});
  }

  void start();

 private:
  boost::asio::io_context m_context;
  boost::asio::ip::tcp::acceptor m_acceptor;
  unordered_map<ConnectionState,
                unique_ptr<unordered_map<int32_t, unique_ptr<InboundPacket>>>>
      m_packet_handlers;

  void start_accept();
  void start_read(const std::shared_ptr<Connection>&);
  void process_buffer(const std::shared_ptr<Connection>&);
};
}  // namespace celerity::net

#endif
