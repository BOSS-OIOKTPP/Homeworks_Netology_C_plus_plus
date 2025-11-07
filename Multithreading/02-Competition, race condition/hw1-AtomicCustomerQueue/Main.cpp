#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>


const int MAX_CLIENTS = 5;
std::atomic<int> clientCount{ 0 };            // Счетчик клиентов
std::atomic<bool> allClientsArrived{ false }; // true - все клиенты обработаны    



// *********************************************************** //
//               Упорядочение доступа к памяти                 //
// *********************************************************** //

// 1.    Последовательное согласование - memory_order_seq_cst  
void clientProcess_SegCst();    // Клиент пришел в очередь. Увеличиваем счетчик
void operatorProcess_SegCst();  // Клиент ушел из очереди. Уменьшаем счетчик

// 2.    Захват - освобождение
void clientProcess_AcqRel();    // Клиент пришел в очередь. Увеличиваем счетчик
void operatorProcess_AcqRel();  // Клиент ушел из очереди. Уменьшаем счетчик

// 3.    Ослабленное - memory_order_relaxed
void clientProcess_Relaxed();    // Клиент пришел в очередь. Увеличиваем счетчик
void operatorProcess_Relaxed();  // Клиент ушел из очереди. Уменьшаем счетчик





int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::cout << "Начало работы. Максимальное количество клиентов: " << MAX_CLIENTS << std::endl << std::endl << std::endl;

    std::cout << "ТЕСТ 1: Доступа к памяти: Последовательное согласование - memory_order_seq_cst" << std::endl << std::endl;
    std::thread clientThread1(clientProcess_SegCst);
    std::thread operatorThread1(operatorProcess_SegCst);
    clientThread1.join();    // Ждем завершение потока
    operatorThread1.join();  // Ждем завершение потока  
    std::cout << std::endl << std::endl << std::endl;



    // Сброс состояния для следующего теста
    clientCount = 0;
    allClientsArrived = false;

    std::cout << "ТЕСТ 2: Доступа к памяти: Захват - освобождение" << std::endl << std::endl;
    std::thread clientThread2(clientProcess_AcqRel);
    std::thread operatorThread2(operatorProcess_AcqRel);
    clientThread2.join();    // Ждем завершение потока
    operatorThread2.join();  // Ждем завершение потока  
    std::cout << std::endl << std::endl << std::endl;


    // Сброс состояния для следующего теста
    clientCount = 0;
    allClientsArrived = false;

    std::cout << "ТЕСТ 3: Доступа к памяти: Ослабленное упорядочение - memory_order_relaxed" << std::endl << std::endl;
    std::thread clientThread3(clientProcess_Relaxed);
    std::thread operatorThread3(operatorProcess_Relaxed);
    clientThread3.join();    // Ждем завершение потока
    operatorThread3.join();  // Ждем завершение потока  
    std::cout << std::endl << std::endl << std::endl;




    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}


// *********************************************************** //
//               Упорядочение доступа к памяти                 //
// *********************************************************** //

// 1.    Последовательное согласование - memory_order_seq_cst
 
// Клиент пришел в очередь. Увеличиваем счетчик
void clientProcess_SegCst() {
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        // Увеличиваем счетчик клиентов                                        т.к. fetch_xxx всегда возвращает значение до изменения, то прибавляем 1
        int currentCount = clientCount.fetch_add(1, std::memory_order_seq_cst) + 1;        
        std::cout << "Пришел клиент. Количество клиентов в очереди: " << currentCount << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
    allClientsArrived.store(true, std::memory_order_seq_cst);
    std::cout << "Все клиенты пришли." << std::endl;
}

// Клиент ушел из очереди. Уменьшаем счетчик
void operatorProcess_SegCst() {
    while (true) {
        if (clientCount.load(std::memory_order_seq_cst) > 0) {
            // Уменьшаем счетчик клиентов                                          т.к. fetch_xxx всегда возвращает значение до изменения
            int currentCount = clientCount.fetch_sub(1, std::memory_order_seq_cst) - 1;
            std::cout << "Клиент обслужен. Количество клиентов в очереди: " << currentCount << std::endl;
        }

        // Если все клиенты пришли и очередь пуста - завершаем работу
        if (allClientsArrived.load(std::memory_order_seq_cst) && 
            clientCount.load(std::memory_order_seq_cst) == 0) 
        {
            std::cout << "Все клиенты обслужены." << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


// 2.    Захват - освобождение

// Клиент пришел в очередь с использованием acquire-release
void clientProcess_AcqRel() {
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        // Увеличиваем счетчик клиентов                                        т.к. fetch_xxx всегда возвращает значение до изменения
        int currentCount = clientCount.fetch_add(1, std::memory_order_acq_rel) + 1;
        std::cout << "Пришел клиент. Количество клиентов в очереди: " << currentCount << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Устанавливаем флаг с release семантикой - гарантируем, что все предыдущие операции выполнены
    allClientsArrived.store(true, std::memory_order_release);
    std::cout << "Все клиенты пришли." << std::endl;
}

// Клиент ушел из очереди 
void operatorProcess_AcqRel() {
    while (true) {        
        if (clientCount.load(std::memory_order_acquire) > 0) {
            // Уменьшаем счетчик клиентов                                          т.к. fetch_xxx всегда возвращает значение до изменения
            int currentCount = clientCount.fetch_sub(1, std::memory_order_acq_rel) - 1;
            std::cout << "Клиент обслужен. Количество клиентов в очереди: " << currentCount << std::endl;
        }        

        // Если все клиенты пришли и очередь пуста - завершаем работу
        if (allClientsArrived.load(std::memory_order_acquire) &&
            clientCount.load(std::memory_order_acquire) == 0)
        {        
            std::cout << "Все клиенты обслужены." << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}


// 3.    Ослабленное - memory_order_relaxed

// Клиент пришел в очередь 
void clientProcess_Relaxed() {
    for (int i = 1; i <= MAX_CLIENTS; ++i) {
        // Увеличиваем счетчик клиентов                                        т.к. fetch_xxx всегда возвращает значение до изменения
        int currentCount = clientCount.fetch_add(1, std::memory_order_relaxed) + 1;
        std::cout << "Пришел клиент. Количество клиентов в очереди: " << currentCount << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    // Устанавливаем флаг 
    allClientsArrived.store(true, std::memory_order_relaxed);
    std::cout << "Все клиенты пришли." << std::endl;
}

// Клиент ушел из очереди 
void operatorProcess_Relaxed() {
    while (true) {        
        if (clientCount.load(std::memory_order_relaxed) > 0) {
            // Уменьшаем счетчик с ослабленной семантикой                          т.к. fetch_xxx всегда возвращает значение до изменения
            int currentCount = clientCount.fetch_sub(1, std::memory_order_relaxed) - 1;
            std::cout << "Клиент обслужен. Количество клиентов в очереди: " << currentCount << std::endl;
        }

        // Если все клиенты пришли и очередь пуста - завершаем работу
        if (allClientsArrived.load(std::memory_order_relaxed) &&
            clientCount.load(std::memory_order_relaxed) == 0)
        {
            std::cout << "Все клиенты обслужены." << std::endl;
            break;
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }
}