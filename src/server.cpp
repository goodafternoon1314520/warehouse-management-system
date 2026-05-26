#include <iostream>
#include <unistd.h>
#include <cstring>
#include <thread>

#include <sys/socket.h>
#include <netinet/in.h>

void handleClient(int clientSocket) {
    char buffer[1024] = {0};

    read(clientSocket, buffer, 1024);

    std::cout << "Client says: " << buffer << std::endl;

    const char* response = "Message received.";

    send(clientSocket, response, strlen(response), 0);

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