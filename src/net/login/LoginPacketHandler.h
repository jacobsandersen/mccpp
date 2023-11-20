//
// Created by simple on 11/17/23.
//

#ifndef MCCPP_LOGINPACKETHANDLER_H
#define MCCPP_LOGINPACKETHANDLER_H


#include <memory>
#include "../Connection.h"
#include "../ByteBuffer.h"

class LoginPacketHandler {
public:
    static void handle_login_packet(const std::shared_ptr<Connection> &, const std::unique_ptr<ByteBuffer> &, size_t *);
};


#endif //MCCPP_LOGINPACKETHANDLER_H
