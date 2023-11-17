#include <iostream>
#include <uuid.h>
#include "PacketLoginInLoginStart.h"

void
PacketLoginInLoginStart::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    std::string username = buffer->read_string(16);
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
}
