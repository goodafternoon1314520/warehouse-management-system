#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>

#include "../include/TokenManager.h"

using json = nlohmann::json;

TokenManager tokenManager;

void handleClient(int clientSocket) {
    char buffer[1024] = {0};

    read(clientSocket, buffer, 1024);

    // std::cout << "Client says: " << buffer << std::endl;

    json request = json::parse(buffer);
    std::string action = request["action"];
    std::cout << "Action" << action << std::endl;

    if (action == "login"){
        std::string username = request["username"];
        std::string password = request["password"];

        // 简化版验证
        if (username == "admin" && password == "123456") {
            std::string token = tokenManager.generateToken(username);

            json response;

            response["status"] = "success";
            response["token"] = token;

            std::string responseText = response.dump();

            send(clientSocket, responseText.c_str(), responseText.length(), 0);
        }
    }

    int id = request["id"];
    int amount = request["amount"];
    std::string token = request["token"];
    std::cout << "Product ID: " << id << std::endl;
    std::cout << "Product amount: " << amount << std::endl;

    if (!tokenManager.validateToken(token)) {
        json response;

        response["status"] = "error";
        response["message"] = "invalid token";

        std::string responseText = response.dump();

        send(clientSocket, responseText.c_str(), responseText.length(), 0);

        close(clientSocket);
        
        return;
    }

    // const char* response = "Message received.";

    json response;
    response["status"] = "success";
    response["message"] = "stock out completed";
    std::string responseText = response.dump();

    send(clientSocket, responseText.c_str(), responseText.length(), 0);

    close(clientSocket);

    std::cout << "Client disconnected!\n";
}

int main() {
    int server_fd;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

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

        std::cout << "Client connected!\n";

        std::thread clientThread(handleClient, clientSocket);

        clientThread.detach();
    }
    close(server_fd);

    return 0;
}