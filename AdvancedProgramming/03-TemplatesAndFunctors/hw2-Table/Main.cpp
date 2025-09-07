#include <iostream>
#include <windows.h>
#include "Table.h"



// Пример использования
int main() {

    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // ТЕСТ 1
    {
        Table<int> t1(2, 3);
        Table<int> t2(2, 3);
        t1 = t2;
    } // Программа может здесь упасть

    std::cout << "// ТЕСТ 1" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "   Table<int> t1(2, 3);" << std::endl;
    std::cout << "   Table<int> t2(2, 3);" << std::endl;
    std::cout << "   t1 = t2;" << std::endl;
    std::cout << "}" << std::endl;
    std::cout << "ТЕСТ 1 выполнился успешно"  << std::endl << std::endl;


    // ТЕСТ 2
    {
        Table<double> t1(2, 3);
        Table<double> t3(t1);
    }

    std::cout << "// ТЕСТ 2" << std::endl;
    std::cout << "{" << std::endl;
    std::cout << "   Table<double> t1(2, 3);" << std::endl;
    std::cout << "   Table<double> t3(t1);" << std::endl;    
    std::cout << "}" << std::endl;
    std::cout << "ТЕСТ 2 выполнился успешно" << std::endl << std::endl;


    std::cout << "ЗАДАНИЕ ПО ДОМАШНЕЙ РАБОТЕ" << std::endl;
    auto test = Table<int>(2, 3);
    test[0][0] = 4; test[0][1] = 0; test[0][2] = 0;
    test[1][0] = 0; test[1][1] = 0; test[1][2] = 0;

    std::cout << "Дан массив: " << std::endl;
    test.Print();
    std::cout << "Размер массива: " << test.Size() << std::endl;
    std::cout << "Элемент [0; 0] = " << test[0][0] << std::endl;

    std::cout << std::endl;
    system("pause");
    


    return EXIT_SUCCESS;
}
