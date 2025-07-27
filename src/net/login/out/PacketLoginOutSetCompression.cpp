#include "PacketLoginOutSetCompression.h"

#include <toml11/value.hpp>

#include "../../../MinecraftServer.h"

namespace celerity::net::login {
void PacketLoginOutSetCompression::write_data(
    const std::shared_ptr<Connection>& conn, ByteBuffer& buffer) {
  toml::value server_config =
      MinecraftServer::get_server()->get_config_manager().get_server_config();
  int16_t compression_threshold =
      toml::find<int16_t>(server_config, "compression_threshold");
  buffer.write_varint(compression_threshold);
}
}  // namespace celerity::net::login
