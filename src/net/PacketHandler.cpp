//
// Created by simple on 11/13/23.
//

#include <iostream>
#include "PacketHandler.h"
#include "handshaking/HandshakingPacketHandler.h"
#include "status/StatusPacketHandler.h"

static void process_buffer(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    std::cout << "process_buffer: " << *bytes_available << " bytes available" << std::endl;

    switch (conn->state) {
        case ConnectionState::Handshaking: {
            std::cout << "Handling \"Handshaking\" packet" << std::endl;
            HandshakingPacketHandler::handle_handshaking_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Status: {
            std::cout << "Handling \"Status\" packet" << std::endl;
            StatusPacketHandler::handle_status_packet(conn, buffer, bytes_available);
            break;
        }

        case ConnectionState::Login: {
            std::cout << "Handling \"Login\" packet" << std::endl;
            break;
        }

        case ConnectionState::Configuration: {
            std::cout << "Handling \"Configuration\" packet" << std::endl;
            break;
        }

        case ConnectionState::Play: {
            std::cout << "Handling \"Play\" packet" << std::endl;
            break;
        }
    }

    if (*bytes_available > 0) {
        process_buffer(conn, buffer, bytes_available);
    } else {
        std::cout << "no more bytes available, returning" << std::endl;
    }
}

void PacketHandler::handle_packet(const std::shared_ptr<Connection> &conn, size_t *bytes_available) {
    std::istream is(&conn->buffer);

    std::unique_ptr<ByteBuffer> buffer = std::make_unique<ByteBuffer>();
    for (int i = 0; i < *bytes_available; i++) {
        char raw;
        is.read(&raw, 1);
        buffer->write_byte(raw);
    }

    process_buffer(conn, buffer, bytes_available);
}

void PacketHandler::send_packet(const std::shared_ptr<Connection> &conn, std::unique_ptr<Packet> packet) {
    std::deque<uint8_t> data = packet->pack()->get_data();
    asio::async_write(
            conn->socket,
            asio::buffer(std::vector(data.begin(), data.end())),
            asio::transfer_all());
}
