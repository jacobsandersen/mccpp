#include <iostream>
#include "PacketStatusInPingRequest.h"
#include "../../PacketHandler.h"

void PacketStatusInPingRequest::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer, size_t *bytes_available) {
    int64_t ping_payload = buffer->read_long();
    std::cout << "Read ping payload: " << ping_payload << std::endl;

    std::cout << "Creating packet" << std::endl;

    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(1);

    std::cout << "writing payload to buffer" << std::endl;

    ByteBuffer buf;
    buf.write_long(ping_payload);

    responsePkt->setData(&buf, buf.get_data_length());

    std::cout << "Sending packet" << std::endl;

    PacketHandler::send_packet(conn, std::move(responsePkt));

    *bytes_available = buffer->get_data_length();
}