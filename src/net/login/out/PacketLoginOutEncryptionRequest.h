#ifndef MCCPP_PACKETLOGINOUTENCRYPTIONREQUEST_H
#define MCCPP_PACKETLOGINOUTENCRYPTIONREQUEST_H

#include <string>
#include <memory>
#include <utility>
#include "../../Connection.h"
#include "../../OutboundPacket.h"

class PacketLoginOutEncryptionRequest : public OutboundPacket {
public:
    PacketLoginOutEncryptionRequest(std::string server_id, int32_t public_key_length, uint8_t *public_key_bytes,
                                    int32_t verify_token_length, uint8_t *verify_token_bytes, bool should_authenticate) :
            OutboundPacket(0x01),
            server_id(std::move(server_id)),
            public_key_length(public_key_length),
            public_key_bytes(public_key_bytes),
            verify_token_length(verify_token_length),
            verify_token_bytes(verify_token_bytes),
            should_authenticate(should_authenticate) {}

    void write_data(const std::shared_ptr<Connection> &conn, ByteBuffer &buffer) override;
private:
    std::string server_id;
    int32_t public_key_length;
    uint8_t *public_key_bytes;
    int32_t verify_token_length;
    uint8_t *verify_token_bytes;
    bool should_authenticate;
};

#endif
