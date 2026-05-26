#include <iostream>
#include <unistd.h>
#include <cstring>

#include <sys/socket.h>
#include <netinet/in.h>

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

    std::cout << "Server started...\n";

    int addrlen = sizeof(address);

    int new_socket = accept(server_fd, (sockaddr*)&address, (socklen_t*)&addrlen);

    std::cout << "Client connected!\n";

    char buffer[1024] = {0};

    read(new_socket, buffer, 1024);

    std::cout << "Client says: " << buffer << std::endl;

    const char* message = "Hello from server";

    send(new_socket, message,strlen(message),0);

    close(new_socket);
    close(server_fd);

    return 0;
}