#ifndef MCCPP_PACKETLOGINOUTLOGINSUCCESS_H
#define MCCPP_PACKETLOGINOUTLOGINSUCCESS_H

#include <string>
#include <cstdint>
#include <memory>
#include <utility>
#include "../../Connection.h"
#include "../../../player/MojangProfile.h"
#include "../../OutboundPacket.h"

class PacketLoginOutLoginSuccess : public OutboundPacket {
public:
    PacketLoginOutLoginSuccess(uuids::uuid unique_id, std::string username,
                               std::vector<MojangProfileProperty> properties) :
            OutboundPacket(0x02),
            m_unique_id(unique_id),
            m_username(std::move(username)),
            m_properties(std::move(properties)) {}

    void write_data(ByteBuffer&) override;
private:
    uuids::uuid m_unique_id;
    std::string m_username;
    std::vector<MojangProfileProperty> m_properties;
};


#endif //MCCPP_PACKETLOGINOUTLOGINSUCCESS_H
