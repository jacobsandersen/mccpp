#include <iostream>
#include "MinecraftServer.h"

int main() {
    try {
        asio::io_context context;

        MinecraftServer server(context, 120);

        std::cout << "Minecraft Server started." << std::endl;
        context.run();
    } catch (const std::exception& err) {
        std::cerr << err.what() << std::endl;
    }
}