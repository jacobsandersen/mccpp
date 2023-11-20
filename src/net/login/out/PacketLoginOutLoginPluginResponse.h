#ifndef MCCPP_PACKETLOGINOUTLOGINPLUGINRESPONSE_H
#define MCCPP_PACKETLOGINOUTLOGINPLUGINRESPONSE_H


#include <cstdint>
#include <memory>
#include <utility>
#include "../../Connection.h"

class PacketLoginOutLoginPluginResponse {
public:
    PacketLoginOutLoginPluginResponse(int32_t message_id, bool successful, std::vector<uint8_t> bytes) :
        m_message_id(message_id),
        m_successful(successful),
        m_bytes(std::move(bytes)) {}

    void send(const std::shared_ptr<Connection>&) const;
private:
    int32_t m_message_id;
    bool m_successful;
    std::vector<uint8_t> m_bytes;
};


#endif
