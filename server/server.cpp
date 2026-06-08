#include <iostream>
#include <unistd.h>
#include <thread>
#include <unordered_map>

#include <sys/socket.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>

#include "../include/TokenManager.h"
#include "../include/ThreadPool.h"
#include "../generated/proto/warehouse.pb.h"
#include "../include/MessageFramer.h"
#include "../include/Session.h"
#include "../include/RSAManager.h"

TokenManager tokenManager;

std::unordered_map<int , Session> sessions;

void handleClient(int clientSocket) {
    warehouse::HandshakeRequest req;
    std::string data;
    if (!MessageFramer::recvMessage(clientSocket, data)) {
        std::cout << "recv handshake failed\n";
        close(clientSocket);
        return;
    }

    if (!req.ParseFromString(data)) {
        std::cout << "Parse handshake failed\n";
        close(clientSocket);
        return;
    }

    // RSA 解密 AES key 和 IV
    std::string aesKeyStr = RSAManager::decrypt(req.encrypted_aes_key(), "../certs/private.pem");
    std::string ivStr = RSAManager::decrypt(req.encrypted_iv(), "../certs/private.pem");

    // 保存 Session
    Session session;
    session.socket = clientSocket;
    session.aesKey.assign(aesKeyStr.begin(), aesKeyStr.end());
    session.iv.assign(ivStr.begin(), ivStr.end());

    sessions[clientSocket] = session;

    // 回复客户端
    warehouse::HandshakeResponse resp;
    resp.set_success(true);
    resp.set_message("Handshake OK");

    std::string handshakeResponseData;
    resp.SerializeToString(&handshakeResponseData);
    auto res = MessageFramer::pack(handshakeResponseData);
    if (!MessageFramer::sendAll(clientSocket, res.data(), res.size()))
        std::cout << "send failed\n";

    std::cout << "handleClient start\n";

    std::string loginRequestData;

    if (!MessageFramer::recvMessage(clientSocket, loginRequestData)) {
        std::cout << "recv message failed\n";
        close(clientSocket);
        return;
    }

    warehouse::LoginRequest request;

    if (!request.ParseFromString(loginRequestData)) {
        std::cout << "Parse protobuf failed\n";
        close(clientSocket);
        return;
    }

    std::string username = request.username();
    std::string password = request.password();
    std::cout << username << std::endl << password << std::endl;

    bool success = username == "admin" && password == "123456";

    warehouse::LoginResponse response;

    if (success) {
        response.set_success(true);
        response.set_token(tokenManager.generateToken(username));
        response.set_message("login success");
    }
    else {
        response.set_success(false);
        response.set_message("login failed");
    }

    std::string responseData;

    if (!response.SerializeToString(&responseData)) {
        std::cout << "Serialize response failed\n";
        close(clientSocket);
        return;
    }

    auto packet = MessageFramer::pack(responseData);
    if (!MessageFramer::sendAll(clientSocket, packet.data(), packet.size()))
        std::cout << "send failed\n";

    close(clientSocket);
}

int main() {
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    ThreadPool pool(4);

    if (server_fd < 0) {
        std::cout << "socket error!\n";
        return 0;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(8080);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "bind error!\n";
        return 0;
    }

    if (listen(server_fd, 3) < 0) {
        std::cout << "listen error!\n";
        return 0;
    }

    std::cout << "Muti-thread Server started...\n";

    while (true) {
        int addrlen = sizeof(address);

        int clientSocket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);

        if (clientSocket < 0) {
            std::cout << "accept error!\n";
            continue;
        }

        std::cout << "Client connected!\n";

        pool.enqueue([clientSocket]{handleClient(clientSocket);});
    }
    close(server_fd);

    return 0;
}