#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>


const int MAX_CLIENTS = 10;
int clientQueue;                // Счетчик клиентов
bool allClientsArrived = false; // true - все клиенты обработаны


void clientProcess() {
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        clientQueue++;          // Увеличиваем счетчик клиентов
        std::cout << "Пришел клиент. Количество клиентов в очереди: " << clientQueue << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    allClientsArrived = true;
    std::cout << "Все клиенты пришли." << std::endl;
}

void operatorProcess() {
    while (true) {
        if (clientQueue>0) {
            clientQueue--;      // Уменьшаем счетчик клиентов
            std::cout << "Клиент обслужен. Количество клиентов в очереди: " << clientQueue << std::endl;
        }

        // Если все клиенты пришли и очередь пуста - завершаем работу
        if (allClientsArrived && clientQueue==0) {
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

