#ifndef MCCPP_OUTBOUNDPACKET_H
#define MCCPP_OUTBOUNDPACKET_H


#include "Connection.h"
#include "ByteBuffer.h"

class OutboundPacket {
public:
    explicit OutboundPacket(int32_t packet_id) : m_packet_id(packet_id) {}

    virtual void write_data(ByteBuffer&) = 0;

    void send(const std::shared_ptr<Connection>&);
private:
    int32_t m_packet_id;
};


#endif
