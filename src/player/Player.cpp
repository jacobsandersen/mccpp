#include "Player.h"

#include <utility>

const std::string &Player::get_username() const {
    return m_username;
}

std::shared_ptr<uuids::uuid> Player::get_unique_id() const {
    return m_unique_id;
}

const std::shared_ptr<Connection> &Player::get_connection() const {
    return m_connection;
}
