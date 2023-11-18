#include <iostream>
#include "MinecraftServer.h"

int main() {
    try {
        std::cout << "Starting Minecraft server..." << std::endl;
        std::thread([](){
            MinecraftServer server;
            server.start();
        }).detach();
        std::cout << "Initialization finished." << std::endl;

        while(true) {}
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}