#include <glog/logging.h>
#include "MinecraftServer.h"

#include "ByteBuffer.h"
#include "nbt/TagCompoundBuilder.h"
#include "nbt/tag/TagString.h"
#include <iostream>

int main(int argc, char* argv[])
{
    google::InitGoogleLogging(argv[0]);
    FLAGS_alsologtostderr = true;

    ByteBuffer buffer;

    const auto test = TagCompoundBuilder::create("hello world")
        ->add(TagString("name", "Bananrama"))
        ->build();

    test.write(buffer);

    for (const auto data = buffer.get_data(); const uint8_t datum : data)
    {
        std::cout << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(datum) << " ";
    }
    std::cout << std::endl;

    try
    {
        MinecraftServer::get_server()->start();
    }
    catch (const std::exception& err)
    {
        LOG(FATAL) << err.what() << std::endl;
    }
}
