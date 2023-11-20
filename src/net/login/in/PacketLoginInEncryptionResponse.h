//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
#define MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H


#include <memory>
#include "../../Connection.h"
#include "../../ByteBuffer.h"

class PacketLoginInEncryptionResponse {
public:
    static void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &, size_t *);
};


#endif //MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
