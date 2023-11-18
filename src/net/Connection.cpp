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
