//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_PACKETSTATUSOUTSTATUSRESPONSE_H
#define MCCPP_PACKETSTATUSOUTSTATUSRESPONSE_H


#include <string>
#include <cstdint>
#include <map>
#include <utility>
#include <memory>
#include "../../Connection.h"
#include "../../OutboundPacket.h"

class PacketStatusOutStatusResponse : public OutboundPacket
{
public:
    PacketStatusOutStatusResponse(std::string version_name, uint16_t protocol_version, uint16_t max_player_count,
                                  uint16_t current_player_count, std::string motd, std::string favicon_base64,
                                  std::map<std::string, std::string> player_sample, bool enforces_secure_chat,
                                  bool previews_chat) :
        OutboundPacket(0x00),
        m_version_name(std::move(version_name)),
        m_protocol_version(protocol_version),
        m_max_player_count(max_player_count),
        m_current_player_count(current_player_count),
        m_motd(std::move(motd)),
        m_favicon_base64(std::move(favicon_base64)),
        m_player_sample(std::move(player_sample)),
        m_enforces_secure_chat(enforces_secure_chat),
        m_previews_chat(previews_chat)
    {
    }

    void write_data(const std::shared_ptr<Connection>& conn, ByteBuffer& buffer) override;

private:
    std::string m_version_name;
    uint16_t m_protocol_version;
    uint16_t m_max_player_count;
    uint16_t m_current_player_count;
    std::string m_motd;
    std::string m_favicon_base64;
    std::map<std::string, std::string> m_player_sample;
    bool m_enforces_secure_chat;
    bool m_previews_chat;
};


#endif
