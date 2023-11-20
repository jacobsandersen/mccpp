#include <iostream>
#include <json/value.h>
#include <json/writer.h>
#include "PacketLoginOutDisconnect.h"
#include "../../Packet.h"
#include "../../PacketHandler.h"

void PacketLoginOutDisconnect::send(const std::shared_ptr<Connection> &conn) const {
    Json::Value response;
    response["text"] = "Login: " + m_reason;
    response["bold"] = true;
    response["color"] = "#D64045";

    std::unique_ptr<Packet> responsePkt = std::make_unique<Packet>(0);

    Json::StreamWriterBuilder builder;
    builder["commentStyle"] = "None";
    builder["indentation"] = "";
    std::string responseStr = Json::writeString(builder, response);

    ByteBuffer buf;
    buf.write_string(responseStr);

    std::cout << "sending disconnect pkt with msg: " << responseStr << std::endl;

    responsePkt->setData(&buf, buf.get_data_length());

    PacketHandler::send_packet(conn, std::move(responsePkt));
}
