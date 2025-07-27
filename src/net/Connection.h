#ifndef MCCPP_CONNECTION_H
#define MCCPP_CONNECTION_H

#include <cryptopp/modes.h>
#include <uuid.h>

#include <boost/any.hpp>
#include <boost/asio.hpp>
#include <deque>

#include "../BasicTimer.h"
#include "../BufferCrypter.h"
#include "../ByteBuffer.h"
#include "../KnownPack.h"

namespace celerity::net {
enum class ConnectionState { Handshaking, Status, Login, Configuration, Play };

enum class BufferReadState {
  ReadPacketLength,
  ReadDataLength,
  DecompressData,
  ReadPacketId,
  HandlePacket
};

struct BufferReadContext {
  BufferReadState read_state = BufferReadState::ReadPacketLength;
  std::unique_ptr<ByteBuffer> partial_buffer = nullptr;
  std::unique_ptr<int32_t> packet_length = nullptr;
  std::unique_ptr<int32_t> data_length = nullptr;
  std::unique_ptr<int32_t> packet_id = nullptr;
};

class Connection {
 public:
  explicit Connection(boost::asio::io_context& context)
      : m_context(context), m_socket(context) {}

  boost::asio::io_context& get_context() const;

  [[nodiscard]] boost::asio::ip::tcp::socket* get_socket();

  [[nodiscard]] ByteBuffer& get_data_buffer();

  [[nodiscard]] BufferReadContext& get_read_context();

  [[nodiscard]] ConnectionState get_state() const;

  void set_state(ConnectionState state);

  bool add_context_value(const std::string& key, boost::any value);

  [[nodiscard]] boost::any get_context_value(const std::string& key) const;

  [[nodiscard]] const std::shared_ptr<uuids::uuid>& get_unique_id() const;

  void set_unique_id(const std::shared_ptr<uuids::uuid>& unique_id);

  void start_new_timer(std::chrono::seconds timeout,
                       const std::function<void()>& callback);

  [[nodiscard]] int64_t get_last_keep_alive_payload() const;

  void set_last_keep_alive_payload(int64_t keep_alive_payload);

  [[nodiscard]] bool get_compress_packets() const;

  void enable_compression();

  [[nodiscard]] bool get_encrypt_packets() const;

  void enable_encryption(const std::vector<uint8_t>& shared_secret);

  BufferCrypter& get_buffer_crypter() const;

  void set_known_packs(std::vector<KnownPack> known_packs);

  std::vector<KnownPack> get_known_packs() const;

  void unclean_close();

 private:
  boost::asio::io_context& m_context;
  boost::asio::ip::tcp::socket m_socket;
  ByteBuffer m_data_buffer{};
  BufferReadContext m_read_context{};
  ConnectionState m_state = ConnectionState::Handshaking;
  std::map<std::string, boost::any> m_context_map;
  int64_t m_last_keep_alive_payload{};
  std::unique_ptr<BasicTimer> m_timer{};
  bool m_compress_packets{};
  bool m_encrypt_packets{};
  std::unique_ptr<BufferCrypter> m_buffer_crypter{};
  std::shared_ptr<uuids::uuid> m_unique_id{};
  std::vector<KnownPack> m_known_packs{};
};
}  // namespace celerity::net

#endif
