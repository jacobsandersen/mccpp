//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETSTATUSOUTPINGRESPONSE_H
#define MCCPP_PACKETSTATUSOUTPINGRESPONSE_H


#include <cstdint>
#include <memory>
#include "../../Connection.h"

class PacketStatusOutPingResponse {
public:
    explicit PacketStatusOutPingResponse(int64_t ping_payload) : m_ping_payload(ping_payload) {}

    void send(const std::shared_ptr<Connection> &) const;

private:
    int64_t m_ping_payload;
};


#endif //MCCPP_PACKETSTATUSOUTPINGRESPONSE_H
