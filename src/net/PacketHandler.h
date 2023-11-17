//
// Created by simple on 11/13/23.
//

#ifndef MCCPP_PACKETHANDLER_H
#define MCCPP_PACKETHANDLER_H


#include "Connection.h"
#include "Packet.h"

class PacketHandler {
public:
    static void handle_packet(const std::shared_ptr<Connection>&, size_t*);
    static void send_packet(const std::shared_ptr<Connection>&, std::unique_ptr<Packet> packet);
};


#endif //MCCPP_PACKETHANDLER_H
