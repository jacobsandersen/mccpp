#ifndef MCCPP_PLAYER_H
#define MCCPP_PLAYER_H

#include <uuid.h>

#include <utility>
#include "../net/Connection.h"

class Player {
public:
    Player(std::shared_ptr<Connection> conn, std::string username, std::shared_ptr<uuids::uuid> unique_id) :
        m_connection(std::move(conn)),
        m_username(std::move(username)),
        m_unique_id(std::move(unique_id)) {}

    [[nodiscard]] const std::shared_ptr<Connection> &get_connection() const;

    [[nodiscard]] const std::string &getUsername() const;

    [[nodiscard]] std::shared_ptr<uuids::uuid> getUniqueId() const;
private:
    std::shared_ptr<Connection> m_connection;
    std::string m_username{};
    std::shared_ptr<uuids::uuid> m_unique_id{};
};

#endif
