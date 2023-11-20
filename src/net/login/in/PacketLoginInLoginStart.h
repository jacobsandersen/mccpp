//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININLOGINSTART_H
#define MCCPP_PACKETLOGININLOGINSTART_H


#include <memory>
#include "../../Connection.h"
#include "../../ByteBuffer.h"

class PacketLoginInLoginStart {
public:
    static void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &, size_t *);
};


#endif //MCCPP_PACKETLOGININLOGINSTART_H
