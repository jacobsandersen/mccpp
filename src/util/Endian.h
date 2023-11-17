//
// Created by simple on 11/10/23.
//

#ifndef MCCPP_ENDIAN_H
#define MCCPP_ENDIAN_H

class Endian {
public:
    static uint16_t convertBigEndianToHost(unsigned short value) {
        return ((value & 0xFF00) >> 8) | ((value & 0x00FF) << 8);
    }

    static uint64_t ntohll(uint64_t number) {
        return ((uint64_t) ntohl(number) << 32) + ((uint64_t) ntohl(number) >> 32);
    }
};



#endif
