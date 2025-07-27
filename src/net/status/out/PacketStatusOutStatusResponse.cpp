#include "PacketStatusOutStatusResponse.h"

#include <json/value.h>
#include <json/writer.h>

namespace celerity::net::status {
void PacketStatusOutStatusResponse::write_data(
    const std::shared_ptr<Connection>& conn, ByteBuffer& buffer) {
  Json::Value response;
  response["version"]["name"] = m_version_name;
  response["version"]["protocol"] = m_protocol_version;
  response["players"]["max"] = m_max_player_count;
  response["players"]["online"] = m_current_player_count;
  response["description"]["text"] = m_motd;
  response["favicon"] = m_favicon_base64;
  response["enforcesSecureChat"] = m_enforces_secure_chat;
  response["previewsChat"] = m_previews_chat;

  Json::StreamWriterBuilder builder;
  std::string responseStr = Json::writeString(builder, response);

  buffer.write_string(responseStr);
}
}  // namespace celerity::net::status
