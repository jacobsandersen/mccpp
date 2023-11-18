//
// Created by simple on 11/17/23.
//

#include <iostream>
#include "NetworkManager.h"
#include "PacketHandler.h"

void NetworkManager::start() {
    start_accept();
    m_context.run();
}

void NetworkManager::start_accept() {
    auto conn = std::make_shared<Connection>(m_context);
    m_acceptor.async_accept(*conn->get_socket(), [this, conn](const asio::error_code &err) {
        if (!err) {
            std::cout << "start_accept: connection established from remote endpoint "
                      << conn->get_socket()->remote_endpoint().address().to_string() << std::endl;

            std::thread([this, conn]() {
                start_read(conn);
            }).detach();

            start_accept();
        } else {
            std::cerr << "start_accept: failed to accept new connection: " << err.message() << std::endl;
        }
    });
}

void NetworkManager::start_read(const std::shared_ptr<Connection> &conn) {
    asio::async_read(
            *conn->get_socket(),
            *conn->get_buffer(),
            asio::transfer_at_least(1),
            [this, conn](const asio::error_code &err, size_t bytes_transferred) {
                if (!err) {
                    PacketHandler::handle_packet(conn, &bytes_transferred);
                    start_read(conn);
                }
            });
}
