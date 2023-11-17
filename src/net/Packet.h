//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_PACKET_H
#define MCCPP_PACKET_H

#include "../VarInt.h"
#include "Connection.h"

class Packet {
public:
    explicit Packet(int32_t packet_id) : Packet(VarInt::encoding_length(packet_id), 0, packet_id, nullptr, false) {}

    Packet(uint32_t packet_length, uint32_t packet_id, ByteBuffer *data) :
        Packet(packet_length, 0, packet_id, data, false) {}

    Packet(uint32_t packet_length, uint32_t data_length, uint32_t packet_id, ByteBuffer *data, bool is_compressed) :
        m_packet_length(packet_length), m_data_length(data_length), m_packet_id(packet_id),
        m_data(data), m_is_compressed(is_compressed) {}

    [[nodiscard]] uint32_t getPacketLength() const;

    void setPacketLength(uint32_t mPacketLength);

    [[nodiscard]] uint32_t getDataLength() const;

    void setDataLength(uint32_t mDataLength);

    [[nodiscard]] uint32_t getPacketId() const;

    [[nodiscard]] ByteBuffer *getData() const;

    void setData(ByteBuffer *mData, uint32_t num_bytes);

    [[nodiscard]] bool isCompressed() const;

    void setCompressed(bool mIsCompressed);

    [[nodiscard]] std::unique_ptr<ByteBuffer> pack() const;

private:
    uint32_t m_packet_length;
    uint32_t m_data_length;
    uint32_t m_packet_id;
    ByteBuffer *m_data;
    bool m_is_compressed;
};

#endif
