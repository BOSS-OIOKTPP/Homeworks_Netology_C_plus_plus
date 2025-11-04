#include <iostream>
#include <windows.h>
#include <thread>
#include <chrono>
#include <vector>
#include <random>
#include <iomanip>



// Вычисляем сумму двух векторов
void calculateVectorSum(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3, int start, int end);

// Функция для 1 потока
double calculateParallelSum1(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3);
// Функция для 2-х потоков
double calculateParallelSum2(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3);
// Функция для 4 потоков
double calculateParallelSum4(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3);
// Функция для 8 потоков
double calculateParallelSum8(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3);
// Функция для 16 потоков
double calculateParallelSum16(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3);




int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);


    // Инициализируем генератор случайных чисел, чтобы при каждом запуске генерировались разные числа
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    // Вывод количества аппаратных ядер
    unsigned int cores = std::thread::hardware_concurrency();
    std::cout << "Количество аппаратных ядер - " << cores << std::endl << std::endl;

    // Эксперимент 1 - 1000 элементов
    std::vector<int> v1_in1(1000);      for (int& x : v1_in1) x = std::rand();
    std::vector<int> v1_in2(1000);      for (int& x : v1_in2) x = std::rand();
    std::vector<int> v1_sum(1000);

    std::vector<int> v2_in1(10000);     for (int& x : v2_in1) x = std::rand();
    std::vector<int> v2_in2(10000);     for (int& x : v2_in2) x = std::rand();
    std::vector<int> v2_sum(10000);

    std::vector<int> v3_in1(100000);    for (int& x : v3_in1) x = std::rand();
    std::vector<int> v3_in2(100000);    for (int& x : v3_in2) x = std::rand();
    std::vector<int> v3_sum(100000);

    std::vector<int> v4_in1(1000000);   for (int& x : v4_in1) x = std::rand();
    std::vector<int> v4_in2(1000000);   for (int& x : v4_in2) x = std::rand();
    std::vector<int> v4_sum(1000000);

    // Устанавливаем фиксированный формат вывода с 7 знаками после запятой
    std::cout << std::fixed << std::setprecision(7);


    // Меняем выравнивание строки влево
    std::cout << std::left;

    // Делаем шапку 
    std::cout << std::setw(13) << " "
              << std::setw(14) << std::left << "1 000"
              << std::setw(14) << std::left << "10 000"
              << std::setw(14) << std::left << "100 000"
              << std::setw(14) << std::left << "1 000 000"
              << std::endl << std::endl;

    // Меняем выравнивание строки вправо
    std::cout << std::right;
    // Выводим время для 1 потока и разных массивов
    std::cout << "1 поток     " 
              << std::setw(10) << calculateParallelSum1(v1_in1, v1_in2, v1_sum) << "s   "
              << std::setw(10) << calculateParallelSum1(v2_in1, v2_in2, v2_sum) << "s   "
              << std::setw(10) << calculateParallelSum1(v3_in1, v3_in2, v3_sum) << "s   "
              << std::setw(10) << calculateParallelSum1(v4_in1, v4_in2, v4_sum) << "s   "
              << std::endl;

    // Выводим время для 2-х потоков и разных массивов
    std::cout << "2 потока    " 
              << std::setw(10) << calculateParallelSum2(v1_in1, v1_in2, v1_sum) << "s   "
              << std::setw(10) << calculateParallelSum2(v2_in1, v2_in2, v2_sum) << "s   "
              << std::setw(10) << calculateParallelSum2(v3_in1, v3_in2, v3_sum) << "s   "
              << std::setw(10) << calculateParallelSum2(v4_in1, v4_in2, v4_sum) << "s   "
              << std::endl;

    // Выводим время для 4-х потоков и разных массивов
    std::cout << "4 потока    "
              << std::setw(10) << calculateParallelSum4(v1_in1, v1_in2, v1_sum) << "s   "
              << std::setw(10) << calculateParallelSum4(v2_in1, v2_in2, v2_sum) << "s   "
              << std::setw(10) << calculateParallelSum4(v3_in1, v3_in2, v3_sum) << "s   "
              << std::setw(10) << calculateParallelSum4(v4_in1, v4_in2, v4_sum) << "s   "
              << std::endl;

    // Выводим время для 8-ми потоков и разных массивов
    std::cout << "8 потоков   "
              << std::setw(10) << calculateParallelSum8(v1_in1, v1_in2, v1_sum) << "s   "
              << std::setw(10) << calculateParallelSum8(v2_in1, v2_in2, v2_sum) << "s   "
              << std::setw(10) << calculateParallelSum8(v3_in1, v3_in2, v3_sum) << "s   "
              << std::setw(10) << calculateParallelSum8(v4_in1, v4_in2, v4_sum) << "s   "
              << std::endl;

    // Выводим время для 16-ти потоков и разных массивов
    std::cout << "16 потоков  "
              << std::setw(10) << calculateParallelSum16(v1_in1, v1_in2, v1_sum) << "s   "
              << std::setw(10) << calculateParallelSum16(v2_in1, v2_in2, v2_sum) << "s   "
              << std::setw(10) << calculateParallelSum16(v3_in1, v3_in2, v3_sum) << "s   "
              << std::setw(10) << calculateParallelSum16(v4_in1, v4_in2, v4_sum) << "s   "
              << std::endl;


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}



// Вычисляем сумму двух векторов
void calculateVectorSum(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3, int start, int end) {
    for (int i = start; i < end; ++i) {
        v3[i] = v1[i] + v2[i];
    }
}

// Функция для 1 потока
double calculateParallelSum1(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3) {
    auto startTime = std::chrono::high_resolution_clock::now();

    // Специально не делаем отдельный поток, чтобы сравнить с многопоточностью
    calculateVectorSum(v1, v2, v3, 0, v1.size());

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

// Функция для 2-х потоков
double calculateParallelSum2(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3) {
    auto startTime = std::chrono::high_resolution_clock::now();

    int part = v1.size() / 2;
    std::thread t1(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), 0, part);
    std::thread t2(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part, v1.size());

    t1.join(); t2.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

// Функция для 4 потоков
double calculateParallelSum4(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3) {
    auto startTime = std::chrono::high_resolution_clock::now();

    int part = v1.size() / 4;
    std::thread t1(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), 0, part);
    std::thread t2(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part, part * 2);
    std::thread t3(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 2, part * 3);
    std::thread t4(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 3, v1.size());

    t1.join(); t2.join(); t3.join(); t4.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

// Функция для 8 потоков
double calculateParallelSum8(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3) {
    auto startTime = std::chrono::high_resolution_clock::now();

    int part = v1.size() / 8;
    std::thread t1(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), 0, part);
    std::thread t2(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part, part * 2);
    std::thread t3(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 2, part * 3);
    std::thread t4(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 3, part * 4);
    std::thread t5(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 4, part * 5);
    std::thread t6(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 5, part * 6);
    std::thread t7(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 6, part * 7);
    std::thread t8(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 7, v1.size());

    t1.join(); t2.join(); t3.join(); t4.join();
    t5.join(); t6.join(); t7.join(); t8.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}

// Функция для 16 потоков
double calculateParallelSum16(const std::vector<int>& v1, const std::vector<int>& v2, std::vector<int>& v3) {
    auto startTime = std::chrono::high_resolution_clock::now();

    int part = v1.size() / 16;
    std::thread t1(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), 0, part);
    std::thread t2(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part, part * 2);
    std::thread t3(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 2, part * 3);
    std::thread t4(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 3, part * 4);
    std::thread t5(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 4, part * 5);
    std::thread t6(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 5, part * 6);
    std::thread t7(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 6, part * 7);
    std::thread t8(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 7, part * 8);
    std::thread t9(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 8, part * 9);
    std::thread t10(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 9, part * 10);
    std::thread t11(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 10, part * 11);
    std::thread t12(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 11, part * 12);
    std::thread t13(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 12, part * 13);
    std::thread t14(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 13, part * 14);
    std::thread t15(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 14, part * 15);
    std::thread t16(calculateVectorSum, std::ref(v1), std::ref(v2), std::ref(v3), part * 15, v1.size());

    t1.join();  t2.join();  t3.join();  t4.join();
    t5.join();  t6.join();  t7.join();  t8.join();
    t9.join();  t10.join(); t11.join(); t12.join();
    t13.join(); t14.join(); t15.join(); t16.join();

    auto endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = endTime - startTime;
    return duration.count();
}