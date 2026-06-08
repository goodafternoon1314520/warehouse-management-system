#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>
#include "../generated/proto/warehouse.pb.h"
#include "../include/Crypto.h"
#include "../include/MessageFramer.h"
#include "../include/RSAManager.h"
#include "../include/SecureChannel.h"

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

    AESContext aesKey = Crypto::generateAESKey();

    // RSA 加密 AES Key/IV
    std::string encKey = RSAManager::encrypt(std::string(aesKey.key.begin(), aesKey.key.end()), "../certs/public.pem");

    std::string encIV = RSAManager::encrypt(std::string(aesKey.iv.begin(), aesKey.iv.end()), "../certs/public.pem");

    // 创建请求
    warehouse::HandshakeRequest req;
    req.set_encrypted_aes_key(encKey);
    req.set_encrypted_iv(encIV);

    // 序列化
    std::string message;
    if (!req.SerializeToString(&message)) {
        std::cout << "Serialize error!\n";
        return -1;
    };

    // 发送
    auto packet = MessageFramer::pack(message);
    if (!MessageFramer::sendAll(sock, packet.data(), packet.size())){
        std::cout << "send failed\n";
        close(sock);
        return -1;
    }

    std::string responseData;
    if (!MessageFramer::recvMessage(sock, responseData)) {
        std::cout << "recv failed!\n";
        return -1;
    }

    warehouse::HandshakeResponse response;
    if (!response.ParseFromString(responseData)) {
        std::cout << "Parse handshake response error!\n";
        close(sock);
        return -1;
    };
    std::cout << "Handshake Success = " <<response.success() << std::endl;
    std::cout << "message = " << response.message() << std::endl;

    warehouse::LoginRequest loginReq;

    loginReq.set_username("admin");
    loginReq.set_password("123456");

    std::string loginData;

    if (!loginReq.SerializeToString(&loginData)) {
        std::cout << "Serialize login failed\n";
        close(sock);
        return -1;
    }

    std::string secureData;

    SecureChannel::encryptMessage(loginData, aesKey.key, secureData);

    auto loginPacket = MessageFramer::pack(secureData);
    if (!MessageFramer::sendAll(sock, loginPacket.data(), loginPacket.size())) {
        std::cout << "Send login failed\n";
        close(sock);
        return -1;
    }

    std::string loginRespData;
    if (!MessageFramer::recvMessage(sock, loginRespData)) {
        std::cout << "Recv login response failed\n";
        close(sock);
        return -1;
    }

    // 解密
    std::string plaintext;
    SecureChannel::decryptMessage(loginRespData, aesKey.key, plaintext);

    warehouse::LoginResponse loginResp;
    if (!loginResp.ParseFromString(plaintext)) {
        std::cout << "Parse login response failed\n";
        close(sock);
        return -1;
    }

    std::cout << "\n===== Login Result =====\n";
    std::cout << "Success: " << loginResp.success() << std::endl;
    std::cout << "Token: " << loginResp.token() << std::endl;
    std::cout << "Message: " << loginResp.message() << std::endl;

    close(sock);

    return 0;
}