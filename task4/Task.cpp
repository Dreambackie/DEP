#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <thread>
#include <fstream>
#include <sstream>

#pragma comment(lib, "Ws2_32.lib")

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

std::string read_file(const std::string& file_path) {
    std::ifstream file(file_path);
    if (!file.is_open()) {
        return "";
    }
    
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

void handle_client(SOCKET client_socket) {
    char buffer[BUFFER_SIZE] = {0};
    
    // Read the request
    int bytes_received = recv(client_socket, buffer, BUFFER_SIZE, 0);
    if (bytes_received == SOCKET_ERROR) {
        std::cerr << "recv failed: " << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        return;
    }
    std::cout << "Request: " << buffer << std::endl;
    
    // Assuming the request is for a file in the current directory
    std::string file_content = read_file("index.html");
    if (file_content.empty()) {
        std::string response = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<h1>404 Not Found</h1>";
        send(client_socket, response.c_str(), response.length(), 0);
    } else {
        std::string response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n" + file_content;
        send(client_socket, response.c_str(), response.length(), 0);
    }
    
    // Close the socket
    closesocket(client_socket);
}

int main() {
    WSADATA wsaData;
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result != 0) {
        std::cerr << "WSAStartup failed: " << result << std::endl;
        return 1;
    }

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET) {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }
    
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) == SOCKET_ERROR) {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    
    if (listen(server_fd, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Listen failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }
    
    std::cout << "Server listening on port " << PORT << std::endl;
    
    while (true) {
        SOCKET client_socket = accept(server_fd, nullptr, nullptr);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "Accept failed: " << WSAGetLastError() << std::endl;
            closesocket(server_fd);
            WSACleanup();
            return 1;
        }
        
        std::thread client_thread(handle_client, client_socket);
        client_thread.detach();
    }
    
    closesocket(server_fd);
    WSACleanup();
    return 0;
}

