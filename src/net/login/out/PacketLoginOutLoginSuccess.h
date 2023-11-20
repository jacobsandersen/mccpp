#ifndef MCCPP_PACKETLOGINOUTLOGINSUCCESS_H
#define MCCPP_PACKETLOGINOUTLOGINSUCCESS_H


#include <string>
#include <cstdint>
#include <memory>
#include "../../Connection.h"
#include "../../../player/MojangProfile.h"

class PacketLoginOutLoginSuccess {
public:
    PacketLoginOutLoginSuccess(uuids::uuid unique_id, std::string username,
                               std::vector<MojangProfileProperty> properties) :
            m_unique_id(unique_id),
            m_username(username),
            m_properties(properties) {}

    void send(const std::shared_ptr<Connection> &) const;

private:
    uuids::uuid m_unique_id;
    std::string m_username;
    std::vector<MojangProfileProperty> m_properties;
};


#endif //MCCPP_PACKETLOGINOUTLOGINSUCCESS_H
