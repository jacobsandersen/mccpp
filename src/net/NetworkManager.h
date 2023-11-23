#ifndef MCCPP_NETWORKMANAGER_H
#define MCCPP_NETWORKMANAGER_H

#include <asio/io_context.hpp>
#include <asio/ip/tcp.hpp>
#include "Connection.h"
#include "InboundPacket.h"
#include "handshaking/in/PacketHandshakingInHandshake.h"
#include "status/in/PacketStatusInStatusRequest.h"
#include "status/in/PacketStatusInPingRequest.h"
#include "login/in/PacketLoginInLoginStart.h"
#include "login/in/PacketLoginInEncryptionResponse.h"
#include "login/in/PacketLoginInLoginPluginResponse.h"
#include "login/in/PacketLoginInLoginAcknowledged.h"
#include "configuration/in/PacketConfigurationInPluginMessage.h"
#include "configuration/in/PacketConfigurationInClientInformation.h"
#include "configuration/in/PacketConfigurationInKeepAlive.h"

using std::unordered_map, std::unique_ptr, std::make_unique;

#define MINECRAFT_PORT 25565

class NetworkManager {
public:
    NetworkManager() :
            m_context(),
            m_acceptor(m_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), MINECRAFT_PORT)),
            m_packet_handlers() {

        // handshaking packets
        auto handshaking_handlers = make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
        handshaking_handlers->insert({0x00, make_unique<PacketHandshakingInHandshake>()});
        m_packet_handlers.insert({ConnectionState::Handshaking, std::move(handshaking_handlers)});

        // status packets
        auto status_handlers = make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
        status_handlers->insert({0x00, make_unique<PacketStatusInStatusRequest>()});
        status_handlers->insert({0x01, make_unique<PacketStatusInPingRequest>()});
        m_packet_handlers.insert({ConnectionState::Status, std::move(status_handlers)});

        // login packets
        auto login_handlers = make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
        login_handlers->insert({0x00, make_unique<PacketLoginInLoginStart>()});
        login_handlers->insert({0x01, make_unique<PacketLoginInEncryptionResponse>()});
        login_handlers->insert({0x02, make_unique<PacketLoginInLoginPluginResponse>()});
        login_handlers->insert({0x03, make_unique<PacketLoginInLoginAcknowledged>()});
        m_packet_handlers.insert({ConnectionState::Login, std::move(login_handlers)});

        // configuration packets
        auto configuration_handlers = make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
        configuration_handlers->insert({0x00, make_unique<PacketConfigurationInClientInformation>()});
        configuration_handlers->insert({0x01, make_unique<PacketConfigurationInPluginMessage>()});
        configuration_handlers->insert({0x03, make_unique<PacketConfigurationInKeepAlive>()});
        m_packet_handlers.insert({ConnectionState::Configuration, std::move(configuration_handlers)});

        // play packets
        auto play_handlers = make_unique<unordered_map<int32_t, unique_ptr<InboundPacket>>>();
        m_packet_handlers.insert({ConnectionState::Play, std::move(play_handlers)});
    }

    void start();

private:
    asio::io_context m_context;
    asio::ip::tcp::acceptor m_acceptor;
    unordered_map<ConnectionState, unique_ptr<unordered_map<int32_t, unique_ptr<InboundPacket>>>> m_packet_handlers;

    void start_accept();
    void start_read(const std::shared_ptr<Connection>&);
    void process_buffer(const std::shared_ptr<Connection>&);
};


#endif
