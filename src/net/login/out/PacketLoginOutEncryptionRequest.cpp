#include <iostream>
#include "PacketLoginOutEncryptionRequest.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketLoginOutEncryptionRequest::send(const std::shared_ptr<Connection> &conn) const {
    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(1);

    ByteBuffer buf;
    if (server_id.length() > 20) {
        buf.write_string(server_id.substr(0, 20), 20);
    } else {
        buf.write_string(server_id, server_id.length());
    }

    buf.write_varint(public_key_length);
    buf.write_ubytes(public_key_bytes, public_key_length);
    buf.write_varint(verify_token_length);
    buf.write_ubytes(verify_token_bytes, verify_token_length);

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
