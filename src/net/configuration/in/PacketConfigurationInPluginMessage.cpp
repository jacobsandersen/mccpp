#include "PacketConfigurationInPluginMessage.h"

void PacketConfigurationInPluginMessage::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    std::string channel = buffer->read_string();
    std::vector<uint8_t> data = buffer->read_ubytes(buffer->get_data_length());
    // TODO: handle
}
