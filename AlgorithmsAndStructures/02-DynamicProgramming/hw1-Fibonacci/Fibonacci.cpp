#include <iostream>
#include <string>
#include <windows.h>

int Fibonacci(int n) {
    if (n <= 0) return 0;    // F(0) = 0
    if (n == 1) return 1;    // F(1) = 1
    return Fibonacci(n - 1) + Fibonacci(n - 2);  // Рекурсия
}

void PrintFibonacci(int n) {
    std::cout << "Последовательность Фибоначчи: ";
    for (int i = 0; i < n; ++i) {
        std::cout << Fibonacci(i);
        if (i != n - 1) 
            std::cout << ", ";  // Запятая после всех чисел, кроме последнего
    }
};


// Функция для вычисления длины строки "F(n)"
int nodeWidth(int n) {
    return 3 + std::to_string(n).length(); // "F(" + to_string(n) + ")"
}

// Функция для вычисления смещения между узлами
int calculateOffset(int n, int level) {
    // Базовое смещение (можно настроить под конкретный случай)
    int base_offset = 4;

    // Уменьшаем смещение с каждым уровнем
    return base_offset * (nodeWidth(n) + 1) / (level + 1);
}

// Рекурсивная функция отрисовки дерева
void drawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int rootPos = 0;

    // Вычисляем позицию корня при первом вызове
    if (isRoot) {
        rootPos = nodeWidth(n) * 2; // Начальное смещение
        pos = rootPos;
    }

    // Отрисовка текущего узла
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << std::endl;

    // Вычисляем смещение для дочерних узлов
    int offset = calculateOffset(n, level);

    // Отрисовка связей
    int left_pos = pos - offset;
    int right_pos = pos + offset;

    // Вычисляем позиции для "/" и "\"
    int slash_pos = pos - offset / 2;
    int backslash_pos = pos + offset / 2;

    std::cout << std::string(slash_pos, ' ') << "/";
    std::cout << std::string(backslash_pos - slash_pos - 1, ' ') << "\\" << std::endl;

    // Рекурсивная отрисовка поддеревьев
    drawFibTree(n - 1, level + 1, left_pos, false);
    drawFibTree(n - 2, level + 1, right_pos, false);
}



/*
// Функция для вычисления длины строки "F(n)"
int NodeWidth(int n) {
    std::string strF = "F(" + std::to_string(n) + ")";    
    return strF.length(); 
}

// Функция для вычисления длины схлопнутой левой ветви  F(1) F(2) F(3) (F4) если n=4
// Используется для вычисления смещения главного узла в консоле
int CollapsedLeftWidth(int n) {
    if (n <= 1) return NodeWidth(n);
    return NodeWidth(n) + 1 + CollapsedLeftWidth(n - 1); // "F(n) " + предыдущие; 1 это дополнительный пробел
}

// Функция для рекурсивной отрисовки дерева
void DrawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int RootOffset = 0;   // Смещение главного узла

    // Вычисляем смещение главного узла при первом вызове
    if (isRoot) {
        RootOffset = CollapsedLeftWidth(n - 1);
        pos = RootOffset;
    }

    // Отрисовка текущего узла
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }
    std::cout << std::endl;

    // Вычисляем смещение для дочерних узлов
    int offset = pow(2, max(n - level, 1)); // Динамическое смещение

    // Отрисовка связей
    int left_pos = pos - offset / 2;
    int right_pos = pos + offset / 2;

    std::cout << std::string(left_pos + NodeWidth(n) / 2, ' ') << "/";
    std::cout << std::string(right_pos - left_pos - NodeWidth(n) + 1, ' ') << "\\" << std::endl;

    // Рекурсивная отрисовка поддеревьев
    DrawFibTree(n - 1, level + 1, left_pos, false);
    DrawFibTree(n - 2, level + 1, right_pos, false);
}
*/





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

    int intN{ 0 };
    int intReplay{ 0 };

    while (true) {
    
        while (true) {
            // Очищаем консоль 
            system("cls");

            std::cout << "Программа рассчитывает числа Фибоначчи рекурсивно по формуле F(n) = F(n-1) + F(n-2) для n > 1" << std::endl;
            std::cout << "Введите количество чисел Фибоначчи в интервале n [0; 10] : ";
            std::cin >> intN;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

            if (intN >= 0 && intN < 11) break;
        }

        // Выводим числа Фибоначчи
        PrintFibonacci(intN);

        std::cout << "\nДерево вызовов для F(" << intN << "):\n";
        drawFibTree(intN);
        
        
        //DrawFibTree(intN);
        //std::cout << std::endl;

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

