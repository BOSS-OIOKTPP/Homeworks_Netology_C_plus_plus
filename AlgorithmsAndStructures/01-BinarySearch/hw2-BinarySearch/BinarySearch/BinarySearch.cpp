#include <iostream>
#include <string>
#include <vector>
#include <windows.h>

void PrintArray(std::vector<int>& arr) {
    std::cout << "[ ";
    bool firstElement = true;  // Первй элемент
    for (const auto& v : arr) {
        if (!firstElement) {
            std::cout << ", " << v;
        }
        else {
            std::cout << v;
            firstElement = false;
        }
    }
    std::cout << " ]" << std::endl;    
};


// Функция считает количество элементов больше чем переданное в функцию целое число
int CountElementsGreaterThan(const std::vector<int>& A, int T) {
    int left = 0;             // Левый индекс рассматриваемого интервала в массиве
    int right = A.size() - 1; // Правый индекс рассматриваемого интервала в массиве
    int res = A.size();       // Изначально считаем, что нет элементов массива больше чем T

    while (left <= right) {
        // находим середину интервала
        int i = left + (right - left) / 2;  

        // если значение элемента массива в i больше Т, то 
        // 1 - устанавливаем новую правую границу левее этого индекса
        if (A[i] > T) {
            res = i;        // т.к. A[i] > T,   то запоминаем этот индекс
            right = i - 1;
        }
        // 2 - иначе устанавливаем новую левую границу правее этого индекса
        else {
            left = i + 1;
        }
    }

    // Количество элементов больше T = Размер массива - индекс первого элемента больше T
    // Пример: 
    //      Сортированный массив { 14, 16, 19, 32, 32, 32, 56, 69, 72 }
    //      Индекс элемента         0   1   2   3   4   5   6   7   8
    //      Количество элементов    9
    //      Значение T              30
    //                          ---------------------------------------
    //      Индекс первого элемента больше T:   3  , тогда     
    //      Количество элементов больше T:      9 - 3 = 6
    return A.size() - res;
}

// *** Итоговое меню   ***
int MenuFinal() {
    int intReplay;
    while (true) {
        // Выводим меню
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "1. Провести еще один расчет" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> intReplay;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intReplay >= 1 && intReplay <= 2) {
            break;
        }
    }
    return intReplay;
}


// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::vector<int> SortedArray = { 14, 16, 19, 32, 32, 32, 56, 69, 72 };
    int intT{0};
    int intReplay{0};

    while (true) {
        // Очищаем консоль 
        system("cls");

        std::cout << "Программа для подсчета количество элементов массива значения которых больше чем число введенное пользователем." << std::endl;
        std::cout << "Дан массив: ";
        PrintArray(SortedArray);
        std::cout << std::endl;

        std::cout << "Введите точку отсчёта: ";
        std::cin >> intT;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        int count = CountElementsGreaterThan(SortedArray, intT);

        std::cout << "Количество элементов в массиве больших, чем " << intT << ": " << count << std::endl;

        // Выводим меню
        intReplay = MenuFinal();
        if (intReplay == 2) break;  // Выходим        
    }

    std::cout << std::endl;
    std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

