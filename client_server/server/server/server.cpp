#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h> 
#include <string>

#pragma comment(lib, "ws2_32.lib")

#define PORT 8080

int main() {
    WSADATA wsaData;
    SOCKET serverSocket = INVALID_SOCKET;
    sockaddr_in serverAddr;
    sockaddr_in clientAddr;
    int clientAddrSize = sizeof(clientAddr);

    // Инициализация Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Создание сокета
    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cerr << "socket failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Настройка адреса сервера
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Любой доступный адрес

    // Связывание сокета с адресом
    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "bind failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    // Начало прослушивания порта
    if (listen(serverSocket, 1) == SOCKET_ERROR) {
        std::cerr << "listen failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    SOCKET clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "accept failed: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Client connected." << std::endl;

    char buffer[512];
    std::string message;

    while (true) {
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived > 0) {
            message = std::string(buffer, bytesReceived);
            if (message == "exit") {
                break;
            }
            std::cout << "Client: " << message << std::endl;
            std::cout << "Server: ";
            std::getline(std::cin, message);
            send(clientSocket, message.c_str(), message.size(), 0);
        }
    }

    // Закрытие сокетов
    closesocket(clientSocket);
    closesocket(serverSocket);
    WSACleanup();

    return 0;
}
