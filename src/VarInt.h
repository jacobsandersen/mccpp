#ifndef CELERITY_VARINT_H
#define CELERITY_VARINT_H

#include "ByteBuffer.h"

namespace celerity {
class VarInt {
 public:
  static int32_t decode_varint(ByteBuffer*, uint8_t*);

  static void encode_varint(int32_t, int8_t*, uint8_t*);

  static int64_t decode_varlong(ByteBuffer*, uint8_t*);

  static void encode_varlong(int64_t, int8_t*, uint8_t*);

  static uint8_t encoding_length(int64_t value);
};
};  // namespace celerity

#endif
