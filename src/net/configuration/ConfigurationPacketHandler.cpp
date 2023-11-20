#include <glog/logging.h>
#include "ConfigurationPacketHandler.h"

void ConfigurationPacketHandler::handle_configuration_packet(const std::shared_ptr<Connection> &conn,
                                                             const std::unique_ptr<ByteBuffer> &buffer,
                                                             size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    LOG(INFO) << "Configuration packet length: " << length;

    int32_t packet_id = buffer->read_varint();
    LOG(INFO) << "Got Configuration packet id: " << packet_id;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        default:
            std::ostringstream os;
            throw std::runtime_error("Illegal configuration packet received");
    }
}
