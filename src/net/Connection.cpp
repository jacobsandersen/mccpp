#include "Connection.h"
#include <glog/logging.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <utility>

#include "../BufferCrypter.h"

boost::asio::io_context& Connection::get_context() const
{
    return m_context;
}

boost::asio::ip::tcp::socket* Connection::get_socket()
{
    return &m_socket;
}

ByteBuffer& Connection::get_data_buffer()
{
    return m_data_buffer;
}

BufferReadContext& Connection::get_read_context()
{
    return m_read_context;
}

ConnectionState Connection::get_state() const
{
    return m_state;
}

void Connection::set_state(ConnectionState state)
{
    m_state = state;
}

bool Connection::add_context_value(const std::string& key, boost::any value)
{
    return m_context_map.emplace(key, value).second;
}

boost::any Connection::get_context_value(const std::string& key) const
{
    return m_context_map.find(key)->second;
}

const std::shared_ptr<uuids::uuid>& Connection::get_unique_id() const
{
    return m_unique_id;
}

void Connection::set_unique_id(const std::shared_ptr<uuids::uuid>& unique_id)
{
    m_unique_id = unique_id;
}

void Connection::start_new_timer(std::chrono::seconds timeout, const std::function<void()>& callback)
{
    if (m_timer != nullptr)
    {
        m_timer->cancel();
    }

    m_timer = std::make_unique<BasicTimer>(m_context);
    m_timer->start(timeout, callback);
}

int64_t Connection::get_last_keep_alive_payload() const
{
    return m_last_keep_alive_payload;
}

void Connection::set_last_keep_alive_payload(int64_t keep_alive_payload)
{
    m_last_keep_alive_payload = keep_alive_payload;
}

bool Connection::get_compress_packets() const
{
    return m_compress_packets;
}

void Connection::enable_compression()
{
    m_compress_packets = true;
}

bool Connection::get_encrypt_packets() const
{
    return m_encrypt_packets;
}

void Connection::enable_encryption(const std::vector<uint8_t>& shared_secret)
{
    if (m_encrypt_packets || m_buffer_crypter != nullptr) return;

    m_encrypt_packets = true;
    m_buffer_crypter = std::make_unique<Celerity::BufferCrypter>(shared_secret);
}

Celerity::BufferCrypter& Connection::get_buffer_crypter() const
{
    if (m_buffer_crypter == nullptr)
    {
        throw std::runtime_error("Encryption is not enabled");
    }

    return *m_buffer_crypter;
}

void Connection::set_known_packs(std::vector<KnownPack> known_packs)
{
    m_known_packs = std::move(known_packs);
}

std::vector<KnownPack> Connection::get_known_packs() const
{
    return m_known_packs;
}

void Connection::unclean_close()
{
    m_socket.close();
}
