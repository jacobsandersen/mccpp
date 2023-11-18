#include <cryptopp/hex.h>
#include <curl/curl.h>
#include <iostream>
#include "PacketLoginInEncryptionResponse.h"
#include "../../../MinecraftServer.h"
#include "../out/PacketLoginOutDisconnect.h"

#define SESSION_URL "https://sessionserver.mojang.com/session/minecraft/hasJoined"

size_t curl_callback_body2string(void *contents, size_t size, size_t nmemb, std::string *s) {
    s->append(static_cast<char *>(contents), size*nmemb);
    return size*nmemb;
}

void PacketLoginInEncryptionResponse::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t shared_secret_length = buffer->read_varint();
    std::vector<uint8_t> shared_secret = buffer->read_ubytes(shared_secret_length);

    int32_t verify_token_length = buffer->read_varint();
    std::vector<uint8_t> verify_token = buffer->read_ubytes(verify_token_length);

    *bytes_available = buffer->get_data_length();

    RSAKeypair keypair = MinecraftServer::get_server()->get_rsa_keypair();

    std::vector<uint8_t> decrypted_verify_token = keypair.decrypt(verify_token);
    decrypted_verify_token.resize(VERIFY_TOKEN_SIZE);

    if (decrypted_verify_token != conn->get_verify_token()) {
        PacketLoginOutDisconnect pkt("Verify token incorrect. Your client is broken.");
        pkt.send(conn);
        return;
    }

    std::vector<uint8_t> decrypted_shared_secret = keypair.decrypt(shared_secret);
    decrypted_shared_secret.resize(SHARED_SECRET_SIZE);

    std::shared_ptr<Player> player = MinecraftServer::get_server()->get_player(conn->get_unique_id());

    std::string digest;
    CryptoPP::SHA1 hash;
    hash.Update(conn->get_shared_secret().data(), SHARED_SECRET_SIZE);
    std::vector<uint8_t> public_key = keypair.get_der_encoded_public_key();
    hash.Update(public_key.data(), public_key.size());
    digest.resize(hash.DigestSize());
    hash.Final((CryptoPP::byte*)&digest[0]);

    std::string encoded;
    CryptoPP::HexEncoder encoder(new CryptoPP::StringSink(encoded));

    CryptoPP::StringSource src(digest, true, new CryptoPP::Redirector(encoder));

    std::cout << "Generated hash: " << encoded << std::endl;

    CURL *curl = curl_easy_init();
    if (!curl) {
        PacketLoginOutDisconnect pkt("Failed to initialize CURL to start your session. Try again later.");
        pkt.send(conn);
        return;
    }

    std::ostringstream stream;
    stream << SESSION_URL << "?username=" << player->get_username() << "&serverId=" << encoded;

    std::string url = stream.str();
    std::string resp_body;

    std::cout << "sending request to" << url << std::endl;

    CURLcode res;
    curl_easy_setopt(curl, CURLOPT_URL, url.data());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, curl_callback_body2string);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resp_body);
    res = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (res != CURLE_OK) {
        PacketLoginOutDisconnect pkt("Session start failed. Try again later.");
        pkt.send(conn);
        return;
    }

    std::cout << resp_body << std::endl;

    std::cout << "Login success. Now to encrypt a packet and send login success, and switch to configuration state." << std::endl;
}
