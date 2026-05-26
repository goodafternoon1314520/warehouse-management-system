#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>
#include <cstring>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

int main() {
    int sock = 0;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in serv_addr{};

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = AF_INET;
    serv_addr.sin_port = htons(8080);

    inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);

    connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

    // const char* message = "Hello Server";

    json request;
    request["action"] = "stock_out";
    request["id"] = 1001;
    request["amount"] = 5;
    std::string message = request.dump();

    send(sock, message.c_str(), message.length(), 0);

    char buffer[1024] = {0};

    read(sock, buffer, 1024);

    // std::cout << "Server says: " << buffer << std::endl;

    json response = json::parse(buffer);
    std::cout << "Status: " << response["status"] << std::endl;
    std::cout << "Message: " << response["message"] << std::endl;

    close(sock);

    return 0;
}