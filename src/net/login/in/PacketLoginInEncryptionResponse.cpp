#include <iostream>
#include "PacketLoginInEncryptionResponse.h"

void PacketLoginInEncryptionResponse::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t shared_secret_length = buffer->read_varint();
    std::cout << "Got shared secret length: " << shared_secret_length << std::endl;

    std::vector<int8_t> shared_secret = buffer->read_bytes(shared_secret_length);
    std::cout << "Got encrypted shared secret." << std::endl;

    int32_t verify_token_length = buffer->read_varint();
    std::cout << "Got verify token length: " << verify_token_length << std::endl;

    std::vector<int8_t> verify_token = buffer->read_bytes(verify_token_length);
    std::cout << "Got encrypted verify token." << std::endl;

    *bytes_available = buffer->get_data_length();
}
