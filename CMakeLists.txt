cmake_minimum_required(VERSION 3.26)
project(mccpp)

set(CMAKE_CXX_STANDARD 17)

find_package(asio REQUIRED)
find_package(jsoncpp REQUIRED)

add_executable(mccpp
        src/main.cpp
        src/MinecraftServer.cpp
        src/VarInt.cpp
        src/util/Endian.h
        src/net/ByteBuffer.cpp
        src/net/Packet.cpp
        src/net/PacketHandler.cpp
        src/net/handshaking/HandshakingPacketHandler.cpp
        src/net/handshaking/in/PacketHandshakingInHandshake.cpp
        src/net/status/StatusPacketHandler.cpp
        src/net/status/in/PacketStatusInStatusRequest.cpp
        src/net/status/in/PacketStatusInPingRequest.cpp
)

target_link_libraries(mccpp asio::asio JsonCpp::JsonCpp)