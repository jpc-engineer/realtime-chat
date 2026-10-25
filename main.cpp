#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cerrno>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (server_fd == -1) {
        std::cerr << "Error: Socket connection failed" << std::endl;
        return 1;
    }

    // Address Structure
    sockaddr_in serverAddress{};
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(7007);

    // Bind to specific IP
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddress.sin_addr) <= 0) {
        std::cerr << "Invalid address/ Address not supported.\n";
        return 1;
    }

    // Bind the socket
    if(bind(server_fd, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
        std::cerr << "Bind failed, Error code: " << errno << "\n";
        close(server_fd);
        return 1;
    }

    std::cout << "Socket successfully bound to IP and port!\n";

    close(server_fd);
    return 0; 
}
