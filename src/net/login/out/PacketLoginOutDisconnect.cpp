#include <iostream>
#include <json/value.h>
#include <json/writer.h>
#include "PacketLoginOutDisconnect.h"

void PacketLoginOutDisconnect::write_data(const std::shared_ptr<Connection>& conn, ByteBuffer& buffer)
{
    Json::Value response;
    response["text"] = "Disconnected during login: " + m_reason;
    response["bold"] = true;
    response["color"] = "#D64045";

    Json::StreamWriterBuilder builder;
    std::string responseStr = Json::writeString(builder, response);

    buffer.write_string(responseStr);
}
