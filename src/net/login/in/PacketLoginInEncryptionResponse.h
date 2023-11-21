//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
#define MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H


#include <memory>
#include "../../Connection.h"
#include "../../ByteBuffer.h"
#include "../../InboundPacket.h"

class PacketLoginInEncryptionResponse : public InboundPacket {
public:
    void handle(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &) override;
};


#endif //MCCPP_PACKETLOGININENCRYPTIONRESPONSE_H
