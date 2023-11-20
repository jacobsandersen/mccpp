#include "Packet.h"

uint32_t Packet::getPacketLength() const {
    return m_packet_length;
}

void Packet::setPacketLength(uint32_t mPacketLength) {
    m_packet_length = mPacketLength;
}

uint32_t Packet::getDataLength() const {
    return m_data_length;
}

void Packet::setCompressed(bool mIsCompressed) {
    m_is_compressed = mIsCompressed;
}

bool Packet::isCompressed() const {
    return m_is_compressed;
}

void Packet::setData(ByteBuffer *mData, uint32_t num_bytes) {
    m_data = mData;
    m_packet_length += num_bytes;
}

ByteBuffer *Packet::getData() const {
    return m_data;
}

void Packet::setDataLength(uint32_t mDataLength) {
    m_data_length = mDataLength;
}

uint32_t Packet::getPacketId() const {
    return m_packet_id;
}

std::unique_ptr<ByteBuffer> Packet::pack(const std::shared_ptr<Connection> &conn) const {
    auto buf = std::make_unique<ByteBuffer>();
    buf->write_varint(static_cast<int32_t>(getPacketLength()));
    buf->write_varint(static_cast<int32_t>(getPacketId()));

    std::deque<uint8_t> data = getData()->get_data();
    buf->write_ubytes(std::vector(data.begin(), data.end()));

    buf->encrypt_buffer(conn);
    return buf;
}