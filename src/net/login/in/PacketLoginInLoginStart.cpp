#include <iostream>
#include <uuid.h>
#include <random>
#include <cryptopp/rsa.h>
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

    uuid_t uuid{};
    auto *data = reinterpret_cast<uint64_t*>(uuid);
    data[0] = uuid_most_significant;
    data[1] = uuid_least_significant;

    // for testing
    char uuidStr[37];
    uuid_unparse(uuid, uuidStr);
    std::cout << "Got uuid logging in: " << uuidStr << std::endl;

    *bytes_available = buffer->get_data_length();

    // below, encryption request
    // TODO: move this elsewhere, clean up pub key encoding & verify token creation

    CryptoPP::RSA::PublicKey *publicKey = conn->get_minecraft_server()->getRSAPublicKey();
    std::vector<uint8_t> encodedPublicKey;
    CryptoPP::VectorSink vs(encodedPublicKey);
    publicKey->DEREncode(vs);
    vs.MessageEnd();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int8_t> dist(std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());

    int8_t randomBytes[4];
    for (int8_t &randomByte : randomBytes) {
        randomByte = dist(gen);
    }

    PacketLoginOutEncryptionRequest resp(
            "",
            static_cast<int32_t>(encodedPublicKey.size()),
            reinterpret_cast<int8_t*>(encodedPublicKey.data()),
            4,
            randomBytes);

    resp.send(conn);
}
