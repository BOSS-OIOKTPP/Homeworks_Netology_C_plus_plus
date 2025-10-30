#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>


const int MAX_CLIENTS = 10;
std::vector<int> clientQueue;   // Вектор для хранения номеров клиентов
bool allClientsArrived = false; // true - все клиенты обработаны


void clientProcess() {
    for (int clientId = 1; clientId <= MAX_CLIENTS; ++clientId) {
        clientQueue.push_back(clientId);  // Добавляем клиента в очередь
        std::cout << "Пришел клиент " << clientId << ". Количество клиентов в очереди: " << clientQueue.size() << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    allClientsArrived = true;
    std::cout << "Все клиенты пришли" << std::endl;
}

void operatorProcess() {
    while (true) {
        if (!clientQueue.empty()) {
            int servedClientId = clientQueue.front();  // Берем первого клиента из очереди
            clientQueue.erase(clientQueue.begin());    // Удаляем его из очереди
            std::cout << "Обслужен клиент " << servedClientId << ". Количество клиентов в очереди: " << clientQueue.size() << std::endl;
        }

        // Если все клиенты пришли и очередь пуста - завершаем работу
        if (allClientsArrived && clientQueue.empty()) {
            std::cout << "Все клиенты обслужены." << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}

int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Начало работы. Максимальное количество клиентов: " << MAX_CLIENTS << std::endl;

    std::thread clientThread(clientProcess);
    std::thread operatorThread(operatorProcess);

    clientThread.join();    // Ждем завершение потока
    operatorThread.join();  // Ждем завершение потока  
    
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

