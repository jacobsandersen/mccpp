#include "PacketStatusInStatusRequest.h"

#include <glog/logging.h>

#include "../out/PacketStatusOutStatusResponse.h"
#include "../../../ConfigManager.h"
#include "../../../MinecraftServer.h"

void
PacketStatusInStatusRequest::handle(const std::shared_ptr<Connection> &conn,
                                    const std::unique_ptr<ByteBuffer> &buffer) {

    LOG(INFO) << "PacketStatusInStatusRequest::handle";

    MinecraftServer *server = MinecraftServer::get_server();
    toml::value server_config = server->get_config_manager().get_server_config();

    uint16_t max_players = toml::find<uint16_t>(server_config, "max_players");
    std::string motd = toml::find<std::string>(server_config, "motd");
    std::string favicon = toml::find<std::string>(server_config, "favicon");

    LOG(INFO) << "Sending PacketStatusOutStatusResponse";

    // TODO: figure out player sample & those booleans
    PacketStatusOutStatusResponse resp(server->get_version_name(), server->get_protocol_version(), max_players,
                                       server->get_players().size(), motd, favicon,
                                       std::map<std::string, std::string>(), false, false);

    resp.send(conn);
}
