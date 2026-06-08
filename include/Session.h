#ifndef SESSION_H
#define SESSION_H

#include <vector>
#include <string>

struct Session {
    int socket; // 客户端socket
    std::vector<unsigned char> aesKey; // 会话 AES Key
    std::vector<unsigned char> iv; // 会话 IV
    std::string token; // Token
};


#endif