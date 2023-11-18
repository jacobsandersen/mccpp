#include "Connection.h"
#include "../MinecraftServer.h"

MinecraftServer *Connection::get_minecraft_server() const {
    return server;
}
