#include <iostream>
#include "ConfigurationPacketHandler.h"

void ConfigurationPacketHandler::handle_configuration_packet(const std::shared_ptr <Connection> &conn, const std::unique_ptr <ByteBuffer> &buffer, size_t *bytes_available) {
    int32_t length = buffer->read_varint();
    std::cout << "Got configuration packet length: " << length << std::endl;

    int32_t packet_id = buffer->read_varint();
    std::cout << "Got configuration packet id: " << packet_id << std::endl;

    *bytes_available = buffer->get_data_length();

    switch (packet_id) {
        default:
            std::ostringstream os;
            os << "Illegal configuration packet \"" << packet_id << "\" received" << std::endl;
            throw std::runtime_error(os.str());
    }
}
