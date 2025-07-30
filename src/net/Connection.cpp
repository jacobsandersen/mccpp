#include "Connection.h"

#include <cryptopp/filters.h>
#include <glog/logging.h>

#include <iostream>
#include <utility>

#include "../BufferCrypter.h"
#include "src/BufferCompressor.h"
#include "src/VarInt.h"

namespace celerity::net {
constexpr uint16_t kReadBufferSize = 8192;

void Connection::start() {
  if (running_) return;
  running_ = true;
  do_read();
}
void Connection::do_read() {
  std::vector<uint8_t> read_buffer;
  read_buffer.resize(kReadBufferSize);

  m_socket.async_read_some(
      boost::asio::buffer(read_buffer),
      [this, read_buffer = std::move(read_buffer)](
          const boost::system::error_code& err,
          const std::size_t bytes_read) mutable {
        if (err) {
          LOG(ERROR) << "Failed to read socket: " + err.message();
          m_socket.shutdown(boost::asio::socket_base::shutdown_both);
          m_socket.close();
          disconnect_callback_(this);
          return;
        }

        read_buffer.resize(bytes_read);

        ByteBuffer tmp(std::move(read_buffer));
        if (this->is_encryption_enabled()) {
          this->get_buffer_crypter().decrypt(tmp);
        }

        m_data_buffer.append(tmp);

        process_buffer();
        do_read();
      });
}

std::optional<DecodedPacket> Connection::try_pop_packet() {
  const auto maybe_packet_length = m_data_buffer.peek_varint();
  if (!maybe_packet_length) {
    return std::nullopt;
  }

  const auto [packet_length, packet_length_num_bytes] = *maybe_packet_length;
  if (m_data_buffer.get_data_length() - packet_length_num_bytes <
      packet_length) {
    return std::nullopt;
  }

  m_data_buffer.truncate_front(packet_length_num_bytes);

  size_t payload_bytes = packet_length;
  bool should_decompress = false;

  if (is_compression_enabled()) {
    uint8_t encoding_length;
    const auto data_length = m_data_buffer.read_varint(&encoding_length);
    payload_bytes -= encoding_length;
    should_decompress = data_length > 0;
  }

  ByteBuffer payload(m_data_buffer.read_ubytes(payload_bytes));
  if (should_decompress) {
    BufferCompressor::decompress(payload);
  }

  return DecodedPacket{payload.read_varint(), payload};
}

void Connection::process_buffer() {
  while (auto maybe_packet = try_pop_packet()) {
    DecodedPacket decoded = std::move(*maybe_packet);
    boost::asio::post(
        incoming_packet_strand_,
        [decoded = std::move(decoded), self = shared_from_this()] mutable {
          self->process_packet(std::move(decoded));
        });
  }
}

void Connection::process_packet(DecodedPacket&& packet) {}

boost::asio::ip::tcp::socket* Connection::get_socket() { return &m_socket; }

ConnectionState Connection::get_state() const { return m_state; }

void Connection::set_state(ConnectionState state) { m_state = state; }

bool Connection::set_context_value(const std::string& key, boost::any value) {
  return m_context_map.insert_or_assign(key, value).second;
}

std::optional<boost::any> Connection::get_context_value(
    const std::string& key) const {
  const auto search = m_context_map.find(key);
  return search == m_context_map.end() ? std::nullopt : search->second;
}

const std::shared_ptr<uuids::uuid>& Connection::get_unique_id() const {
  return m_unique_id;
}

void Connection::set_unique_id(const std::shared_ptr<uuids::uuid>& unique_id) {
  m_unique_id = unique_id;
}

void Connection::start_new_timer(std::chrono::seconds timeout,
                                 const std::function<void()>& callback) {
  if (m_timer != nullptr) {
    m_timer->cancel();
  }

  m_timer = std::make_unique<BasicTimer>(m_socket.get_executor());
  m_timer->start(timeout, callback);
}

int64_t Connection::get_keep_alive_payload() const {
  const auto keep_alive = get_context_value("keep_alive");
  if (!keep_alive || keep_alive->empty()) {
    return -1;
  }

  try {
    return boost::any_cast<int64_t>(*keep_alive);
  } catch (boost::bad_any_cast&) {
    return -1;
  }
}

bool Connection::is_compression_enabled() const {
  const auto compression = get_context_value("compression");
  if (!compression || compression->empty()) {
    return false;
  }

  try {
    return boost::any_cast<bool>(*compression);
  } catch (boost::bad_any_cast&) {
    return false;
  }
}

void Connection::enable_compression() {
  set_context_value("compression", true);
}

bool Connection::is_encryption_enabled() const {
  const auto encryption = get_context_value("encryption");
  if (!encryption || encryption->empty()) {
    return false;
  }

  try {
    return boost::any_cast<bool>(*encryption);
  } catch (boost::bad_any_cast&) {
    return false;
  }
}

void Connection::enable_encryption(const std::vector<uint8_t>& shared_secret) {
  if (is_encryption_enabled() || m_buffer_crypter != nullptr) return;

  set_context_value("encryption", true);
  m_buffer_crypter = std::make_unique<BufferCrypter>(shared_secret);
}

BufferCrypter& Connection::get_buffer_crypter() const {
  if (m_buffer_crypter == nullptr) {
    throw std::runtime_error("Encryption is not enabled");
  }

  return *m_buffer_crypter;
}

void Connection::set_known_packs(std::vector<KnownPack> known_packs) {
  m_known_packs = std::move(known_packs);
}

std::vector<KnownPack> Connection::get_known_packs() const {
  return m_known_packs;
}

void Connection::unclean_close() { m_socket.close(); }
}  // namespace celerity::net