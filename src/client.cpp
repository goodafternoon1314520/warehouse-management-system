#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>
#include "../generated/proto/warehouse.pb.h"
#include "../include/Crypto.h"
#include "../include/MessageFramer.h"

int main() {
    int sock = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    if (connect(sock, (sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
        std::cout << "connect error!\n";
        return -1;
    };

    // AESContext aesKey = Crypto::generateAESKey();

    // 创建请求
    warehouse::LoginRequest req;
    req.set_username("admin");
    req.set_password("123456");

    // 序列化
    std::string message;
    if (!req.SerializeToString(&message)) {
        std::cout << "Serialize error!\n";
        return -1;
    };

    // std::string encryptedData = Crypto::encryptAES(message, aesKey.key, aesKey.iv);

    // 发送
    auto packet = MessageFramer::pack(message);
    if (!MessageFramer::sendAll(sock, packet.data(), packet.size())){
        std::cout << "send failed\n";
        return -1;
    }

    std::string responseData;
    if (!MessageFramer::recvMessage(sock, responseData)) {
        std::cout << "recv failed!\n";
        return -1;
    }

    warehouse::LoginResponse response;
    if (!response.ParseFromString(responseData)) {
        std::cout << "Parse response error!\n";
        return -1;
    };
    std::cout << "success = " <<response.success() << std::endl;
    std::cout << "token = " << response.token() << std::endl;
    std::cout << "message = " << response.message() << std::endl;

    close(sock);

    return 0;
}