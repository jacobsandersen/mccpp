#include <glog/logging.h>
#include <random>
#include <uuid.h>
#include <cryptopp/filters.h>
#include "PacketLoginInLoginStart.h"
#include "../out/PacketLoginOutEncryptionRequest.h"
#include "../../../MinecraftServer.h"
#include "../out/PacketLoginOutDisconnect.h"

void
PacketLoginInLoginStart::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    std::string username = buffer->read_string();
    LOG(INFO) << "Username: " << username;

    uuids::uuid unique_id = buffer->read_uuid();
    LOG(INFO) << "Unique ID: " << uuids::to_string(unique_id);

    auto unique_id_ptr = std::make_shared<uuids::uuid>(unique_id);
    conn->set_unique_id(unique_id_ptr);

    Player player(conn, username, unique_id_ptr);
    MinecraftServer::get_server()->add_player(std::make_shared<Player>(player));

    // below, encryption request
    // TODO: move this elsewhere, clean up verify token creation

    std::vector<uint8_t> encoded_public_key = MinecraftServer::get_server()->get_rsa_keypair().get_der_encoded_public_key();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<uint8_t> dist(0, std::numeric_limits<uint8_t>::max());

    std::vector<uint8_t> verify_token;
    for (int i = 0; i < VERIFY_TOKEN_SIZE; i++) {
        verify_token.push_back(dist(gen));
    }

    conn->set_verify_token(verify_token);

    PacketLoginOutEncryptionRequest resp(
            "",
            static_cast<int32_t>(encoded_public_key.size()),
            encoded_public_key.data(),
            VERIFY_TOKEN_SIZE,
            verify_token.data());

    resp.send(conn);
}
