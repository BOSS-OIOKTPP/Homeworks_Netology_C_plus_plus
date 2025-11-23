#include <iostream>
#include <winsock2.h>
#include <ws2tcpip.h>
//#include <string>
#include <thread>

#pragma comment(lib, "ws2_32.lib") // Линкуем библиотеку Winsock


class TcpServer {
private:
    WSAData _wsa_data_;
    SOCKET _socket_;
    sockaddr_in _server_addr_{}, _client_addr_{};
    char* _buffer_ = new char[32];
    int _port_ = 12345;

    // Функция для обработки клиента в отдельном потоке
    void handle_client(SOCKET client_socket) {
        int size_data = recv(client_socket, _buffer_, 32, 0);
        if (size_data > 0) {
            _buffer_[size_data] = '\0';  
            std::cout << _buffer_ << std::endl;
            std::string answer = "Hello from server";
            send(client_socket, answer.c_str(), answer.size(), 0);
        }
        closesocket(client_socket);
    }
public:
    TcpServer() {
        int err = WSAStartup(MAKEWORD(2, 2), &_wsa_data_);        
        _socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);   
        _server_addr_.sin_family = AF_INET;
        _server_addr_.sin_addr.s_addr = INADDR_ANY;
        _server_addr_.sin_port = htons(_port_);
        int err_s = bind(_socket_, (sockaddr*)&_server_addr_, sizeof(_server_addr_));
        if (err_s == SOCKET_ERROR) {
            std::cout << "Сокет не создан" << std::endl;
            closesocket(_socket_);
            WSACleanup();
            return;
        }
        // прослушиваем порт
        if (listen(_socket_, SOMAXCONN) == SOCKET_ERROR) {
            std::cout << "Ошибка прослушивания порта" << std::endl;
            closesocket(_socket_);
            WSACleanup();
            return;
        }
    }
    ~TcpServer() {
        closesocket(_socket_);
        WSACleanup();
    }

    void recieve_and_answer() {
        int client_size = sizeof(_client_addr_);
        
        while (true) {
            std::cout << "Ждем подключения клиента…" << std::endl;
            SOCKET client_socket = accept(_socket_, (sockaddr*)&_client_addr_, &client_size);
            std::cout << "Клиент подключен, создаем поток..." << std::endl;

            // Создаем отдельный поток для обработки клиента
            std::thread client_thread(&TcpServer::handle_client, this, client_socket);
            client_thread.detach(); // Отсоединяем поток
        }
    }

};


int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    TcpServer server;
    server.recieve_and_answer();
        

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}