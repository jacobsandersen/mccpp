#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <boost/asio.hpp>
#include <uuid.h>
#include <deque>
#include <cryptopp/modes.h>
#include "../ByteBuffer.h"
#include "../BasicTimer.h"
#include "../KnownPack.h"

#define VERIFY_TOKEN_SIZE 4
#define SHARED_SECRET_SIZE 16

enum class ConnectionState
{
    Handshaking,
    Status,
    Login,
    Configuration,
    Play
};

enum class BufferReadState
{
    ReadPacketLength,
    ReadDataLength,
    DecompressData,
    ReadPacketId,
    HandlePacket
};

struct BufferReadContext
{
    BufferReadState read_state = BufferReadState::ReadPacketLength;
    std::unique_ptr<ByteBuffer> partial_buffer = nullptr;
    std::unique_ptr<int32_t> packet_length = nullptr;
    std::unique_ptr<int32_t> data_length = nullptr;
    std::unique_ptr<int32_t> packet_id = nullptr;
};

class Connection
{
public:
    explicit Connection(boost::asio::io_context& context) : m_context(context), m_socket(context), m_read_context()
    {
    }

    boost::asio::io_context& get_context() const;

    [[nodiscard]] boost::asio::ip::tcp::socket* get_socket();

    [[nodiscard]] ByteBuffer& get_data_buffer();

    [[nodiscard]] BufferReadContext& get_read_context();

    [[nodiscard]] ConnectionState get_state() const;

    void set_state(ConnectionState state);

    [[nodiscard]] const std::shared_ptr<uuids::uuid>& get_unique_id() const;

    void set_unique_id(const std::shared_ptr<uuids::uuid>& unique_id);

    [[nodiscard]] const std::vector<uint8_t>& get_verify_token() const;

    void set_verify_token(const std::vector<uint8_t>& verifyToken);

    [[nodiscard]] const std::vector<uint8_t>& get_shared_secret() const;

    void start_new_timer(std::chrono::seconds timeout, const std::function<void()>& callback);

    [[nodiscard]] int64_t get_last_keep_alive_payload() const;

    void set_last_keep_alive_payload(int64_t keep_alive_payload);

    void set_shared_secret(const std::vector<uint8_t>& sharedSecret);

    [[nodiscard]] bool get_compress_packets() const;

    void enable_compression();

    [[nodiscard]] bool get_encrypt_packets() const;

    void enable_encryption();

    std::deque<uint8_t> encrypt_bytes(std::deque<uint8_t>);

    std::deque<uint8_t> decrypt_bytes(std::deque<uint8_t>);

    void set_known_packs(std::vector<KnownPack> known_packs);

    std::vector<KnownPack> get_known_packs() const;

    void unclean_close();

private:
    boost::asio::io_context& m_context;
    boost::asio::ip::tcp::socket m_socket;
    ByteBuffer m_data_buffer{};
    BufferReadContext m_read_context{};
    ConnectionState m_state = ConnectionState::Handshaking;
    std::vector<uint8_t> m_verify_token{};
    std::vector<uint8_t> m_shared_secret{};
    int64_t m_last_keep_alive_payload{};
    std::unique_ptr<BasicTimer> m_timer{};
    bool m_compress_packets{};
    bool m_encrypt_packets{};
    std::shared_ptr<uuids::uuid> m_unique_id{};
    CryptoPP::CFB_Mode_ExternalCipher::Encryption m_cfb_stream_cipher_encryption{};
    CryptoPP::CFB_Mode_ExternalCipher::Decryption m_cfb_stream_cipher_decryption{};
    std::vector<KnownPack> m_known_packs{};
};

#endif
