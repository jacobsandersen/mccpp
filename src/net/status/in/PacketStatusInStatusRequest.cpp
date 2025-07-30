#include "PacketStatusInStatusRequest.h"

#include <glog/logging.h>

#include "../../../ConfigManager.h"
#include "../../../MinecraftServer.h"
#include "../out/PacketStatusOutStatusResponse.h"

namespace celerity::net::status {
void PacketStatusInStatusRequest::handle(
    const std::shared_ptr<Connection>& conn,
    const std::unique_ptr<ByteBuffer>& buffer) {
  LOG(INFO) << "Received status request, collecting information...";

  MinecraftServer* server = MinecraftServer::get_server();
  const auto server_config = server->get_config_manager().get_server_config();

  const auto max_players = server_config.get_max_players();
  const auto motd = server_config.get_motd();
  const auto favicon = server_config.get_favicon();

  LOG(INFO) << "Information collected, sending status...";

  // TODO: figure out player sample & those booleans
  PacketStatusOutStatusResponse resp(
      server->get_version_name(), server->get_protocol_version(), max_players,
      server->get_players().size(), motd, favicon,
      std::map<std::string, std::string>(), false, false);

  resp.send(conn);
}
}  // namespace celerity::net::status
