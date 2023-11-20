//
// Created by simple on 11/13/23.
//

#include <glog/logging.h>
#include "PacketHandler.h"
#include "handshaking/HandshakingPacketHandler.h"
#include "status/StatusPacketHandler.h"
#include "login/LoginPacketHandler.h"
#include "configuration/ConfigurationPacketHandler.h"

static void process_buffer(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer,
                           size_t *bytes_available) {
    LOG(INFO) << "Processing buffer. " << *bytes_available << " bytes are available.";

    LOG(INFO) << "process_buffer: decrypting buffer if necessary...";
    buffer->decrypt_buffer(conn);

    switch (conn->get_state()) {
        case ConnectionState::Handshaking: {
            LOG(INFO) << "Handling a Handshaking packet.";
            HandshakingPacketHandler::handle_handshaking_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Status: {
            LOG(INFO) << "Handling a Status packet.";
            StatusPacketHandler::handle_status_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Login: {
            LOG(INFO) << "Handling a Login packet.";
            LoginPacketHandler::handle_login_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Configuration: {
            LOG(INFO) << "Handling a Configuration packet.";
            ConfigurationPacketHandler::handle_configuration_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Play: {
            LOG(INFO) << "Handling a Play packet.";
            break;
        }
    }

    if (*bytes_available > 0) {
        process_buffer(conn, buffer, bytes_available);
    } else {
        LOG(INFO) << "Buffer exhausted. Going back to get more bytes!";
    }
}

void PacketHandler::handle_packet(const std::shared_ptr<Connection> &conn, size_t *bytes_available) {
    std::istream is(conn->get_buffer());

    std::unique_ptr<ByteBuffer> buffer = std::make_unique<ByteBuffer>();
    for (int i = 0; i < *bytes_available; i++) {
        char raw;
        is.read(&raw, 1);
        buffer->write_byte(raw);
    }

    process_buffer(conn, buffer, bytes_available);
}

void PacketHandler::send_packet(const std::shared_ptr<Connection> &conn, std::unique_ptr<Packet> packet) {
    std::deque<uint8_t> data = packet->pack(conn)->get_data();

    LOG(INFO) << "Writing a packet to the network.";

    asio::async_write(
            *conn->get_socket(),
            asio::buffer(std::vector(data.begin(), data.end())),
            asio::transfer_all());
}
