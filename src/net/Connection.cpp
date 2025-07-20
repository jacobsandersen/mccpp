#include "Connection.h"
#include <glog/logging.h>
#include <cryptopp/aes.h>
#include <cryptopp/filters.h>
#include <iostream>
#include <utility>

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

const std::shared_ptr<uuids::uuid>& Connection::get_unique_id() const
{
    return m_unique_id;
}

void Connection::set_unique_id(const std::shared_ptr<uuids::uuid>& unique_id)
{
    m_unique_id = unique_id;
}

const std::vector<uint8_t>& Connection::get_verify_token() const
{
    return m_verify_token;
}

void Connection::set_verify_token(const std::vector<uint8_t>& verifyToken)
{
    m_verify_token = verifyToken;
}

const std::vector<uint8_t>& Connection::get_shared_secret() const
{
    return m_shared_secret;
}

void Connection::set_shared_secret(const std::vector<uint8_t>& sharedSecret)
{
    m_shared_secret = sharedSecret;
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

void Connection::enable_encryption()
{
    if (m_encrypt_packets)
    {
        return;
    }

    m_encrypt_packets = true;

    std::vector<uint8_t> shared_secret_vec = get_shared_secret();
    CryptoPP::SecByteBlock shared_secret(shared_secret_vec.data(), shared_secret_vec.size());

    auto aes = new CryptoPP::AES::Encryption(shared_secret, SHARED_SECRET_SIZE);
    m_cfb_stream_cipher_encryption = CryptoPP::CFB_Mode_ExternalCipher::Encryption(*aes, shared_secret, 1);
    m_cfb_stream_cipher_decryption = CryptoPP::CFB_Mode_ExternalCipher::Decryption(*aes, shared_secret, 1);
}

std::deque<uint8_t> Connection::encrypt_bytes(std::deque<uint8_t> bytes)
{
    if (!get_encrypt_packets())
    {
        return bytes;
    }

    auto enc_bytes_tmp = std::vector<uint8_t>{};

    CryptoPP::VectorSource src(std::vector(bytes.begin(), bytes.end()), true,
                               new CryptoPP::StreamTransformationFilter(
                                   m_cfb_stream_cipher_encryption,
                                   new CryptoPP::VectorSink(enc_bytes_tmp)));

    auto enc_bytes = std::deque<uint8_t>();
    for (uint8_t byte : enc_bytes_tmp)
    {
        enc_bytes.push_back(byte);
    }

    return enc_bytes;
}

std::deque<uint8_t> Connection::decrypt_bytes(std::deque<uint8_t> enc_bytes)
{
    if (!get_encrypt_packets())
    {
        return enc_bytes;
    }

    auto bytes_tmp = std::vector<uint8_t>{};

    CryptoPP::VectorSource src(std::vector(enc_bytes.begin(), enc_bytes.end()), true,
                               new CryptoPP::StreamTransformationFilter(
                                   m_cfb_stream_cipher_decryption,
                                   new CryptoPP::VectorSink(bytes_tmp)));

    auto bytes = std::deque<uint8_t>();
    for (uint8_t byte : bytes_tmp)
    {
        bytes.push_back(byte);
    }

    return bytes;
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
