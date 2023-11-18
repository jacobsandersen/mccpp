#ifndef MCCPP_PACKETLOGINOUTDISCONNECT_H
#define MCCPP_PACKETLOGINOUTDISCONNECT_H


#include <string>
#include <memory>
#include <utility>
#include "../../Connection.h"

class PacketLoginOutDisconnect {
public:
    explicit PacketLoginOutDisconnect(std::string reason) : m_reason(std::move(reason)) {}

    void send(const std::shared_ptr<Connection>&) const;
private:
    std::string m_reason;
};

#endif
