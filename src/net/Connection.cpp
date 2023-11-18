#include "Connection.h"
#include "../MinecraftServer.h"

asio::ip::tcp::socket *Connection::get_socket() {
    return &m_socket;
}

asio::streambuf *Connection::get_buffer() {
    return &m_buffer;
}

ConnectionState Connection::get_state() const {
    return m_state;
}

void Connection::set_state(ConnectionState state) {
    m_state = state;
}

const std::vector<uint8_t> &Connection::get_verify_token() const {
    return m_verify_token;
}

void Connection::set_verify_token(const std::vector<uint8_t> &verifyToken) {
    m_verify_token = verifyToken;
}

const std::vector<uint8_t> &Connection::get_shared_secret() const {
    return m_shared_secret;
}

void Connection::set_shared_secret(const std::vector<uint8_t> &sharedSecret) {
    m_shared_secret = sharedSecret;
}

const std::shared_ptr<uuids::uuid> &Connection::get_unique_id() const {
    return m_unique_id;
}

void Connection::set_unique_id(const std::shared_ptr<uuids::uuid> &unique_id) {
    m_unique_id = unique_id;
}
