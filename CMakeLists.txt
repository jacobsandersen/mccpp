cmake_minimum_required(VERSION 3.26)
project(mccpp)

set(CMAKE_CXX_STANDARD 17)

find_package(asio REQUIRED)
find_package(jsoncpp REQUIRED)
find_package(cryptopp REQUIRED)
find_package(stduuid REQUIRED)
find_package(CURL REQUIRED)
find_package(panzi-portable-endian REQUIRED)
find_package(toml11 REQUIRED)
find_package(glog REQUIRED)
find_package(gflags REQUIRED)
find_package(ZLIB REQUIRED)

add_executable(mccpp
        src/main.cpp
        src/MinecraftServer.cpp
        src/ConfigManager.cpp
        src/VarInt.cpp
        src/RSAKeypair.cpp
        src/util/UUIDUtil.cpp
        src/player/Player.cpp
        src/player/MojangProfile.cpp
        src/net/ByteBuffer.cpp
        src/net/Connection.cpp
        src/net/NetworkManager.cpp
        src/net/HttpClient.cpp
        src/net/OutboundPacket.cpp
        src/net/handshaking/in/PacketHandshakingInHandshake.cpp
        src/net/status/in/PacketStatusInStatusRequest.cpp
        src/net/status/in/PacketStatusInPingRequest.cpp
        src/net/status/out/PacketStatusOutStatusResponse.cpp
        src/net/status/out/PacketStatusOutPingResponse.cpp
        src/net/login/in/PacketLoginInLoginStart.cpp
        src/net/login/in/PacketLoginInEncryptionResponse.cpp
        src/net/login/in/PacketLoginInLoginAcknowledged.cpp
        src/net/login/in/PacketLoginInLoginPluginResponse.cpp
        src/net/login/out/PacketLoginOutEncryptionRequest.cpp
        src/net/login/out/PacketLoginOutDisconnect.cpp
        src/net/login/out/PacketLoginOutLoginSuccess.cpp
        src/net/login/out/PacketLoginOutLoginPluginRequest.cpp
)

target_link_libraries(mccpp asio::asio JsonCpp::JsonCpp cryptopp::cryptopp stduuid::stduuid CURL::libcurl
        panzi-portable-endian::panzi-portable-endian toml11::toml11 glog::glog gflags::gflags ZLIB::ZLIB)