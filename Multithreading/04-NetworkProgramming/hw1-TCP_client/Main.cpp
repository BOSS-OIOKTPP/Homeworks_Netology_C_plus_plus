#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib") // Линкуем библиотеку Winsock

int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    // === 1. Инициализация Winsock ===
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "WSAStartup failed.\n";
        return 1;
    }

    // === 2. Создание сокета ===
    SOCKET clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Socket creation failed.\n";
        WSACleanup();
        return 1;
    }

    // === 3. Настройка адреса сервера ===
    sockaddr_in serverAddr{};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(12345); // Порт сервера
    inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr); // IP-адрес сервера

    // === 4. Подключение к серверу ===
    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Unable to connect to server.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Connected to server.\n";

    // === 5. Отправка сообщения ===
    const char* message = "Hello from C++ TCP client!";
    if (send(clientSocket, message, strlen(message), 0) == SOCKET_ERROR) {
        std::cerr << "Send failed.\n";
        closesocket(clientSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Message sent: " << message << "\n";

    // === 6. Получение ответа ===
    char buffer[1024] = { 0 };
    int bytesReceived = recv(clientSocket, buffer, sizeof(buffer) - 1, 0);
    if (bytesReceived > 0) {
        std::cout << "Received from server: " << buffer << "\n";
    }
    else if (bytesReceived == 0) {
        std::cout << "Connection closed by server.\n";
    }
    else {
        std::cerr << "recv failed.\n";
    }

    // === 7. Завершение работы ===
    closesocket(clientSocket);
    WSACleanup();



    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}