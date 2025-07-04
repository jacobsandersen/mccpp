#include <glog/logging.h>
#include "MinecraftServer.h"

int main(int argc, char* argv[]) {
    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = true;

    try {
        MinecraftServer::get_server()->start();
    } catch (const std::exception &err) {
        LOG(FATAL) << err.what() << std::endl;
    }
}