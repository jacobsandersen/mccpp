#include <iostream>
#include <random>
#include <uuid.h>
#include <cryptopp/filters.h>
#include "PacketLoginInLoginStart.h"
#include "../out/PacketLoginOutEncryptionRequest.h"
#include "../../../MinecraftServer.h"

void
PacketLoginInLoginStart::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    std::string username = buffer->read_string();
    std::cout << "Got username logging in: " << username << std::endl;

    uint64_t uuid_most_significant = buffer->read_ulong();
    uint64_t uuid_least_significant = buffer->read_ulong();
    std::array<uuids::uuid::value_type, 16> uuid_bytes{};
    std::memcpy(uuid_bytes.data(), &uuid_most_significant, sizeof(uint64_t));
    std::memcpy(uuid_bytes.data() + 8, &uuid_least_significant, sizeof(uint64_t));
    uuids::uuid unique_id(uuid_bytes);
    std::cout << "Got unique id of user logging in: " << uuids::to_string(unique_id) << std::endl;

    Player player(conn, username, std::make_shared<uuids::uuid>(unique_id));
    MinecraftServer::get_server()->add_player(std::make_shared<Player>(player));

    *bytes_available = buffer->get_data_length();

    // below, encryption request
    // TODO: move this elsewhere, clean up verify token creation

    std::vector<uint8_t> encoded_public_key = MinecraftServer::get_server()->get_rsa_keypair().get_der_encoded_public_key();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int8_t> dist(std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());

    int8_t randomBytes[4];
    for (int8_t &randomByte : randomBytes) {
        randomByte = dist(gen);
    }

    PacketLoginOutEncryptionRequest resp(
            "",
            static_cast<int32_t>(encoded_public_key.size()),
            reinterpret_cast<int8_t*>(encoded_public_key.data()),
            4,
            randomBytes);

    resp.send(conn);
}
