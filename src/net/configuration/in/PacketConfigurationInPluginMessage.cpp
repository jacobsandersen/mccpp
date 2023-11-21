#include <glog/logging.h>
#include "PacketConfigurationInPluginMessage.h"

void PacketConfigurationInPluginMessage::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Received a configuration plugin message";

    std::string channel = buffer->read_string();
    LOG(INFO) << "Channel: " << channel;

    std::vector<uint8_t> data = buffer->read_ubytes(buffer->get_data_length());

    LOG(INFO) << "Got all data from plugin message, but not doing anything with it for now.";
}
