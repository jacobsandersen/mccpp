#include <cryptopp/hex.h>
#include <json/value.h>
#include <json/reader.h>
#include "PacketLoginInEncryptionResponse.h"
#include "../../../MinecraftServer.h"
#include "../out/PacketLoginOutDisconnect.h"
#include "../../HttpClient.h"
#include "../../../util/UUIDUtil.h"
#include "../out/PacketLoginOutLoginSuccess.h"
#include "../out/PacketLoginOutSetCompression.h"

#define SESSION_URL "https://sessionserver.mojang.com/session/minecraft/hasJoined"

void performTwosCompliment(ByteBuffer& buffer)
{
    bool carry = true;
    for (int32_t i = static_cast<int32_t>(buffer.get_data_length()) - 1; i >= 0; --i)
    {
        uint8_t value = buffer.peek_ubyte(i);
        uint8_t newByte = ~value & 0xff;
        if (carry)
        {
            carry = newByte == 0xff;
            buffer.write_ubyte(carry ? 0 : newByte + 1, i);
        }
        else
        {
            buffer.write_ubyte(newByte, i);
        }
    }
}

std::string mcHexDigest(const std::string& hashIn)
{
    ByteBuffer buffer;
    for (char byte : hashIn)
    {
        buffer.write_ubyte(static_cast<uint8_t>(byte));
    }

    bool negative = buffer.peek_byte() < 0;
    if (negative)
    {
        performTwosCompliment(buffer);
    }

    std::string result;
    std::deque<uint8_t> data = buffer.get_data();
    auto vector_data = std::vector<uint8_t>(data.begin(), data.end());

    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(result), false, 2, "");
    encoder.Put(vector_data.data(), vector_data.size());
    encoder.MessageEnd();

    result.erase(0, result.find_first_not_of('0'));

    if (negative)
    {
        result = "-" + result;
    }

    return result;
}

void PacketLoginInEncryptionResponse::handle(const std::shared_ptr<Connection>& conn,
                                             const std::unique_ptr<ByteBuffer>& buffer)
{
    int32_t shared_secret_length = buffer->read_varint();
    std::vector<uint8_t> shared_secret = buffer->read_ubytes(shared_secret_length);

    int32_t verify_token_length = buffer->read_varint();
    std::vector<uint8_t> verify_token = buffer->read_ubytes(verify_token_length);

    RSAKeypair keypair = MinecraftServer::get_server()->get_rsa_keypair();

    std::vector<uint8_t> decrypted_verify_token = keypair.decrypt(verify_token);
    decrypted_verify_token.resize(VERIFY_TOKEN_SIZE);

    std::vector<uint8_t> decrypted_shared_secret = keypair.decrypt(shared_secret);
    decrypted_shared_secret.resize(SHARED_SECRET_SIZE);
    conn->set_shared_secret(decrypted_shared_secret);
    conn->enable_encryption();

    if (decrypted_verify_token != conn->get_verify_token())
    {
        auto pkt = new PacketLoginOutDisconnect("Verify token incorrect. Your client is broken.");
        pkt->send(conn);
        delete pkt;
        return;
    }

    std::shared_ptr<Player> player = MinecraftServer::get_server()->get_player(conn->get_unique_id());

    std::string hash;
    CryptoPP::SHA1 sha1;
    sha1.Update(decrypted_shared_secret.data(), SHARED_SECRET_SIZE);
    std::vector<uint8_t> public_key = keypair.get_der_encoded_public_key();
    sha1.Update(public_key.data(), public_key.size());
    hash.resize(sha1.DigestSize());
    sha1.Final((CryptoPP::byte*)&hash[0]);

    std::string finalDigest = mcHexDigest(hash);

    std::map<std::string, std::string> params;
    params.insert({"username", player->get_username()});
    params.insert({"serverId", finalDigest});

    std::string resp_body;
    int64_t resp_code{};
    bool request_status = HttpClient::get_url(SESSION_URL, params, &resp_body, &resp_code);
    if (!request_status || resp_code != 200)
    {
        PacketLoginOutDisconnect pkt("Failed to register your session with Mojang. Try again later.");
        pkt.send(conn);
        return;
    }

    Json::Value resp_json;
    Json::Reader reader;
    if (!reader.parse(resp_body, resp_json))
    {
        PacketLoginOutDisconnect pkt("Failed to parse Mojang's response. Mojang issue? Try again later.");
        pkt.send(conn);
        return;
    }

    std::vector<MojangProfileProperty> properties;
    for (auto property : resp_json["properties"])
    {
        std::string signature;
        if (property.isMember("signature"))
        {
            signature = property["signature"].asString();
        }

        properties.emplace_back(property["name"].asString(), property["value"].asString(), signature);
    }

    std::string canonicalized_unique_id = UUIDUtil::canonicalize_uuid(resp_json["id"].asString());

    auto maybe_unique_id = uuids::uuid::from_string(canonicalized_unique_id);
    if (!maybe_unique_id.has_value())
    {
        PacketLoginOutDisconnect pkt("Failed to parse your UUID. Try again later.");
        pkt.send(conn);
        return;
    }

    auto unique_id = maybe_unique_id.value();

    MojangProfile profile(unique_id, resp_json["name"].asString(), properties);

    player->set_mojang_profile(std::make_shared<MojangProfile>(profile));

    toml::value server_config = MinecraftServer::get_server()->get_config_manager().get_server_config();
    int16_t compression_threshold = toml::find<int16_t>(server_config, "compression_threshold");
    if (compression_threshold >= 0)
    {
        PacketLoginOutSetCompression set_compression{};
        set_compression.send(conn);
        conn->enable_compression();
    }

    PacketLoginOutLoginSuccess resp(unique_id, player->get_username(), properties);
    resp.send(conn);
}
