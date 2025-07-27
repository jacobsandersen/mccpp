cmake_minimum_required(VERSION 3.31)
project(celerity)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_BUILD_TYPE Debug)

find_package(boost_asio CONFIG REQUIRED)
find_package(boost_endian CONFIG REQUIRED)
find_package(boost_any CONFIG REQUIRED)
find_package(jsoncpp CONFIG REQUIRED)
find_package(cryptopp CONFIG REQUIRED)
find_package(stduuid CONFIG REQUIRED)
find_package(CURL REQUIRED)
find_package(toml11 CONFIG REQUIRED)
find_package(glog CONFIG REQUIRED)
find_package(gflags CONFIG REQUIRED)
find_package(ZLIB REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(ICU REQUIRED IMPORTED_TARGET icu-i18n icu-io icu-uc)

add_executable(celerity src/main.cpp)

target_sources(celerity PRIVATE
        src/MinecraftServer.cpp
        src/ConfigManager.cpp
        src/VarInt.cpp
        src/RSAKeypair.cpp
        src/ByteBuffer.cpp
        src/BasicTimer.cpp
        src/KnownPack.cpp
        src/BufferCompressor.cpp
        src/BufferCrypter.cpp
        src/util/UUIDUtil.cpp
        src/player/Player.cpp
        src/player/MojangProfile.cpp
        src/player/ClientInformation.cpp
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
        src/net/login/out/PacketLoginOutSetCompression.cpp
        src/net/configuration/in/PacketConfigurationInClientInformation.cpp
        src/net/configuration/in/PacketConfigurationInPluginMessage.cpp
        src/net/configuration/in/PacketConfigurationInKeepAlive.cpp
        src/net/configuration/out/PacketConfigurationOutKeepAlive.cpp
        src/net/configuration/out/PacketConfigurationOutDisconnect.cpp
        src/net/configuration/out/PacketConfigurationOutRegistryData.cpp
        src/net/configuration/out/PacketConfigurationOutFeatureFlags.cpp
        src/net/configuration/out/PacketConfigurationOutKnownPacks.cpp
        src/net/configuration/in/PacketConfigurationInKnownPacks.cpp
        src/nbt/TagCompoundBuilder.cpp
        src/nbt/tag/TagType.cpp
        src/nbt/tag/TagByte.cpp
        src/nbt/tag/TagCompound.cpp
        src/nbt/tag/TagEnd.cpp
        src/nbt/tag/TagShort.cpp
        src/nbt/tag/TagInt.cpp
        src/nbt/tag/TagLong.cpp
        src/nbt/tag/TagDouble.cpp
        src/nbt/tag/TagFloat.cpp
        src/nbt/tag/TagByteArray.cpp
        src/nbt/tag/TagString.cpp
        src/nbt/tag/TagIntArray.cpp
        src/nbt/tag/TagLongArray.cpp
)

target_link_libraries(celerity PRIVATE
        Boost::asio Boost::endian Boost::any JsonCpp::JsonCpp cryptopp::cryptopp stduuid
        CURL::libcurl toml11::toml11 glog::glog gflags::gflags ZLIB::ZLIB
        PkgConfig::ICU
)