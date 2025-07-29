#include <glog/logging.h>

#include <iostream>

#include "ByteBuffer.h"
#include "MinecraftServer.h"
#include "nbt/NBTWriter.h"
#include "nbt/TagCompoundBuilder.h"
#include "nbt/tag/TagString.h"

int main(int argc, char* argv[]) {
  google::InitGoogleLogging(argv[0]);
  FLAGS_alsologtostderr = true;

  celerity::ByteBuffer my_buffer;
  celerity::nbt::NBTWriter writer(my_buffer);

  auto test =
      celerity::nbt::TagCompoundBuilder::create("hello world")
          ->add("name", celerity::nbt::tag::TagString("Bananrama"))
          ->build();

  writer.write_tag(test);

  std::cout << "Test NBT write:" << std::endl;
  std::cout << my_buffer.to_hex_string() << std::endl;

  try {
    celerity::MinecraftServer::get_server()->start();
  } catch (const std::exception& err) {
    LOG(FATAL) << err.what() << std::endl;
  }
}
