//
// Created by simple on 11/17/23.
//

#include <memory>
#include <json/value.h>
#include <json/writer.h>
#include "PacketStatusOutStatusResponse.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketStatusOutStatusResponse::send(const std::shared_ptr<Connection> &conn) {
    Json::Value response;
    response["version"]["name"] = m_version_name;
    response["version"]["protocol"] = m_protocol_version;
    response["players"]["max"] = m_max_player_count;
    response["players"]["online"] = m_current_player_count;
    response["description"]["text"] = m_motd;
    response["favicon"] = m_favicon_base64;
    response["enforcesSecureChat"] = m_enforces_secure_chat;
    response["previewsChat"] = m_previews_chat;

    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(0);

    Json::StreamWriterBuilder builder;
    std::string responseStr = Json::writeString(builder, response);

    ByteBuffer buf;
    buf.write_string(responseStr);

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
