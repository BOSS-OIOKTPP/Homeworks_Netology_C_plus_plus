// hw2-Class.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

//Задача 2. Класс
//В этом задании вы вынесете класс в отдельный файл.
//
//Возьмите класс счётчика из предыдущего домашнего задания.
//
//Вынесите этот класс в отдельный файл, продемонстрируйте работу программы таким же образом, как в предыдущем домашнем задании.
//
//Пример работы программы
//Консоль
//Вы хотите указать начальное значение счётчика ? Введите да или нет : да
//Введите начальное значение счётчика : 6
//Введите команду('+', '-', '=' или 'x') : +
//Введите команду('+', '-', '=' или 'x') : +
//Введите команду('+', '-', '=' или 'x') : =
//8
//Введите команду('+', '-', '=' или 'x') : -
//Введите команду('+', '-', '=' или 'x') : =
//7
//Введите команду('+', '-', '=' или 'x') : x
//До свидания!

#include <iostream>
#include <locale>
#include "Calculator.h"


int main()
{
    setlocale(LC_ALL, "russian");

    char chContinue{ 'Y' };
    double num1{ 0.0 };
    double num2{ 0.0 };

    Calculator calc;
    bool setValue{ true };

    while (true) {
        system("cls");  // Очищаем консоль

        // Вводим num1
        do {
            std::cout << "Введите num1 : ";
            std::cin >> num1;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели строку, иначе зациклится
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки
            // сохраняем значение в поле объекта
            setValue = calc.set_num1(num1);
            if (setValue == false) {
                std::cout << "Неверный ввод!" << std::endl;
            }
        } while (setValue == false);

        // Вводим num2
        do {
            std::cout << "Введите num2 : ";
            std::cin >> num2;
            std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели строку, иначе зациклится
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки
            // сохраняем значение в поле объекта
            setValue = calc.set_num2(num2);
            if (setValue == false) {
                std::cout << "Неверный ввод!" << std::endl;
            }
        } while (setValue == false);

        // Выводим результат на экран
        std::cout << "num1 + num2 = " << calc.add() << std::endl;
        std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << calc.multiply() << std::endl;
        std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;
        std::cout << std::endl;

        std::cout << "Для повторного продолжения нажмите - 'Y' или 'y : '";

        std::cin >> chContinue;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки

        if (chContinue != 'Y' && chContinue != 'y') {
            break;
        }
    }
    return 0;
}
