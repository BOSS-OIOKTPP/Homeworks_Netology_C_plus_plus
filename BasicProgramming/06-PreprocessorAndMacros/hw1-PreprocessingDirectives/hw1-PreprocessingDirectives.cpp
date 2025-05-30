﻿// hw1-PreprocessingDirectives.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//Задача 1. Препроцессорные директивы
//В этом задании вы используете некоторые препроцессорные директивы, которые вы изучили ранее.
//
//В вашей программе выполните действия :
//
//Объявите символьную константу MODE с целочисленным значением.
//Проверьте, что константа определена, иначе программа не должна скомпилироваться и должна выдать сообщение о необходимости определить MODE.
//В случае, если MODE имеет значение 0, выведите на консоль «Работаю в режиме тренировки».
//Если MODE имеет значение 1, определите функцию add, которая должна складывать два числа.Выведите на консоль «Работаю в боевом режиме», попросите пользователя ввести два числа и выведите результат сложения с помощью функции add на консоль.
//Если MODE имеет любое другое значение, выведите на консоль «Неизвестный режим.Завершение работы».
//Обратите внимание : функция add должна быть определена только, если MODE имеет значение 1.
//
//Пример работы программы
//Консоль
//Работаю в боевом режиме
//Введите число 1 : 4
//Введите число 2 : 6
//Результат сложения : 10

#include <iostream>
#include <locale>


#define MODE 1

#ifndef MODE
   #error "Необходимости определить константу MODE"
#endif

#if MODE == 1
    int Add( int A, int B) {return A + B; }
#endif


int main()
{
    setlocale(LC_ALL, "russian");

    #if MODE == 0 
        std::cout << "Работаю в режиме тренировки\n";
    #elif MODE == 1 
        std::cout << "Работаю в боевом режиме\n";

        int A{ 0 };
        int B{ 0 };

        // Вводим A
        std::cout << "Введите число 1: ";
        std::cin >> A;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки

        // Вводим B
        std::cout << "Введите число 2: ";
        std::cin >> B;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "результат сложения: " << Add(A, B) << std::endl;

    #else
        std::cout << "Неизвестный режим.Завершение работы\n";
        return 1;
    #endif
}

