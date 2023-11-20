#include "PacketLoginInLoginPluginRequest.h"
#include "../out/PacketLoginOutLoginPluginResponse.h"

void PacketLoginInLoginPluginRequest::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t message_id = buffer->read_varint();
    std::string channel = buffer->read_string();
    std::vector<uint8_t> bytes = buffer->read_ubytes(buffer->get_data_length());

    *bytes_available = buffer->get_data_length();

    // we do not understand your request.
    PacketLoginOutLoginPluginResponse resp(message_id, false, bytes);
    resp.send(conn);
}
