#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#pragma comment(lib, "ws2_32.lib") // Линкуем библиотеку Winsock


class UpdClient {
private:
    WSAData _wsa_data_;
    SOCKET _socket_;
    sockaddr_in _server_addr_{};
    char* _buffer_ = new char[32] {};
    int _port_ = 12345;
public:
    UpdClient() {
        int err = WSAStartup(MAKEWORD(2, 2), &_wsa_data_);
        _socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        _server_addr_.sin_family = AF_INET;
        std::string ip = "127.0.0.1";
        _server_addr_.sin_addr.s_addr = inet_addr(ip.c_str());
        _server_addr_.sin_port = htons(_port_);        
    }
    ~UpdClient() {
        closesocket(_socket_);
        WSACleanup();
    }

    void send_text() {
        // устанавливаем соединение с сервером
        if (connect(_socket_, (sockaddr*)&_server_addr_, sizeof(_server_addr_)) == SOCKET_ERROR) {
            std::cout << "Не удалось подключиться к серверу" << std::endl;
            return;
        }
        std::string hello = "Hello from client";
        send(_socket_, hello.c_str(), hello.size(), 0);
        int size_data = recv(_socket_, _buffer_, 32, 0);
        if (size_data > 0) {
            _buffer_[size_data] = '\0';
            std::cout << _buffer_ << std::endl;
        }
    }

};


int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    UpdClient client;
    client.send_text();

    
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}