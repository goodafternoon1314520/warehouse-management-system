#include "../include/MessageFramer.h"

#include <cstdint>
#include <arpa/inet.h>
#include <cstring>
#include <sys/socket.h>

std::vector<char> MessageFramer::pack(const std::string& data) {
    uint32_t len = htonl(data.size());

    std::vector<char> buffer(sizeof(len) + data.size());

    // 写长度
    std::memcpy(buffer.data(), &len, sizeof(len));

    // 写正文
    std::memcpy(buffer.data() + sizeof(len), data.data(), data.size());

    return buffer;
}

bool MessageFramer::recvMessage(int socketFd, std::string& outData) {
    // 读长度
    uint32_t netLen;
    int ret = recv(socketFd, &netLen, sizeof(netLen), MSG_WAITALL);
    if (ret <= 0)
        return false;

    // 转换
    uint32_t len = ntohl(netLen);
    if (len == 0)
        return false;

    // 创建缓冲区
    std::vector<char> buffer(len);

    // 读取正文
    ret = recv(socketFd, buffer.data(), len, MSG_WAITALL);
    if (ret <= 0)
        return false;

    outData.assign(buffer.begin(), buffer.end());

    return true;
}

bool MessageFramer::sendAll(int socketFd, const char* data, size_t length) {
    size_t totalSent = 0;

    while (totalSent < length) {
        ssize_t sent = send(socketFd, data + totalSent, length - totalSent, 0);
        if (sent <= 0)
            return false;
        totalSent += sent;
    }
    return true;
}