#include <iostream>
#include <toml.hpp>
#include "MinecraftServer.h"

int main() {
    try {
        std::thread([](){
            MinecraftServer *server = MinecraftServer::get_server();
            server->start();
        }).join();
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}