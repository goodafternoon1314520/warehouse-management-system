#ifndef MESSAGE_FRAMER_H
#define MESSAGE_FRAMER_H

#include <vector>
#include <string>

class MessageFramer {
public:
    // 封装
    static std::vector<char> pack(const std::string& data);

    static bool recvMessage(int socketFd, std::string& outData);

    static bool sendAll(int socketFd, const char* data, size_t length);
};


#endif