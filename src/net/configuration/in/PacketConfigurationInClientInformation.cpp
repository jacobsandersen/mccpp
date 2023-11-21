#include <glog/logging.h>
#include <bitset>
#include "PacketConfigurationInClientInformation.h"

void PacketConfigurationInClientInformation::handle(const std::shared_ptr<Connection> &conn, const std::unique_ptr<ByteBuffer> &buffer) {
    LOG(INFO) << "Received client information";

    std::string locale = buffer->read_string();
    LOG(INFO) << "Locale: " << locale;

    int8_t view_distance = buffer->read_byte();
    LOG(INFO) << "View distance: " << static_cast<int>(view_distance) << " chunks";

    int32_t chat_mode = buffer->read_varint();
    LOG(INFO) << "Chat mode: " << chat_mode;

    bool chat_colors_enabled = buffer->read_boolean();
    LOG(INFO) << "Chat colors enabled?: " << chat_colors_enabled;

    uint8_t displayed_skin_parts = buffer->read_ubyte();
    LOG(INFO) << "Displayed skin parts: 0b" << std::bitset<8>(displayed_skin_parts);

    int32_t main_hand = buffer->read_varint();
    LOG(INFO) << "Main hand: " << main_hand;

    bool enable_text_filtering = buffer->read_boolean();
    LOG(INFO) << "Enable text filtering: " << enable_text_filtering;

    bool allow_server_listings = buffer->read_boolean();
    LOG(INFO) << "Allow server listings: " << allow_server_listings;
}
