//
// Created by Jacob Andersen on 7/22/25.
//

#ifndef BUFFERCOMPRESSOR_H
#define BUFFERCOMPRESSOR_H
#include "ByteBuffer.h"

namespace celerity {
enum BufferCompressionType { GZIP, ZLIB, NONE };

class BufferCompressor {
 public:
  static BufferCompressionType detect_compression_type(ByteBuffer& buffer);
  static ByteBuffer& compress(ByteBuffer& buffer, BufferCompressionType type);
  static ByteBuffer& decompress(ByteBuffer& buffer);
};
}  // namespace celerity

#endif  // BUFFERCOMPRESSOR_H
