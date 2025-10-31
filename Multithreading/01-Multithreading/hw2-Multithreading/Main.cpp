#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <random>

// Параллельное вычисление суммы
double calculateParallelSum(std::vector<int>& v1, std::vector<int>& v2, std::vector<int>& v3, int countThreads);



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Вывод количества аппаратных ядер
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Количество аппаратных ядер - " << cores << std::endl << std::endl;

    std::vector<int> v1_1(1000);      for (int& x : v1_1) x = std::rand();
    std::vector<int> v1_2(1000);      for (int& x : v1_2) x = std::rand();
    std::vector<int> v1_3(1000);

    std::vector<int> v2_1(10000);     for (int& x : v2_1) x = std::rand();
    std::vector<int> v2_2(10000);     for (int& x : v2_2) x = std::rand();
    std::vector<int> v2_3(10000);

    std::vector<int> v3_1(100000);    for (int& x : v3_1) x = std::rand();
    std::vector<int> v3_2(100000);    for (int& x : v3_2) x = std::rand();
    std::vector<int> v3_3(100000);

    std::vector<int> v4_1(1000000);   for (int& x : v4_1) x = std::rand();
    std::vector<int> v4_2(1000000);   for (int& x : v4_2) x = std::rand();
    std::vector<int> v4_3(1000000);



    std::cout << "Начало работы. Максимальное количество клиентов: " << MAX_CLIENTS << std::endl;

    std::thread clientThread(clientProcess);
    std::thread operatorThread(operatorProcess);

    clientThread.join();    // Ждем завершение потока
    operatorThread.join();  // Ждем завершение потока  
    
    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

// Функция для вычисления суммы части вектора
void calculatePartialSum(int start, int end) {
    for (int i = start; i < end; ++i) {
        result[i] = vec1[i] + vec2[i];
    }
}

double calculateParallelSum1(std::vector<int>& v1, std::vector<int>& v2, std::vector<int>& v3, int countThreads) {
    auto startTime = std::chrono::high_resolution_clock::now();

    std::vector<std::thread> threads;
    int chunkSize = v3.size() / countThreads;

    for (int i = 0; i < countThreads; ++i) {
        int start = i * chunkSize;
        int end = (i == countThreads - 1) ? v3.size() : (i + 1) * chunkSize;

        threads.emplace_back(&VectorSumCalculator::calculatePartialSum, this, start, end);
    }


    for (int i = 0; i < v3.size(); ++i)
        v3[i] = v1[i] + v2[i];
        
    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;

    return duration.count();
}
