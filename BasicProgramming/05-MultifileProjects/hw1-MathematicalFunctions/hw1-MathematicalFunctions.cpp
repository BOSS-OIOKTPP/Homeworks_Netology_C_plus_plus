// hw1-MathematicalFunctions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>
#include <string>
#include "MathFunctions.h"

class NumPair {
private:
    int FA;          // 1 число
    int FB;          // 2 число
    int FOperation;  // номер операции над числами: 1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень
public:
    
    // Метод устанавливает значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. 
    // Возвращает true, если установка произошла успешно, в обратном случае false
    void SetA(int A) { FA = A; }
    int GetA() { return FA; }

    void SetB(int B) { FB = B; }
    int GetB() { return FB; }

    void SetOperation(int Operation) { FOperation = Operation; }
    int GetOperation() { return FOperation; }

    bool Checked(std::string& Err) {
        return false;
    }       
};



int main()
{
    setlocale(LC_ALL, "russian");

    char chContinue{ 'Y' };
    int A{0};
    int B{0};
    int Operation{0};
    
    bool bChecked{ true };

    while (true) {
        system("cls");  // Очищаем консоль

        // Вводим A
        std::cout << "Введите первое число: ";
        std::cin >> A;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки

        // Вводим B
        std::cout << "Введите второе число: ";
        std::cin >> B;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 

        // Выбираем операцию
        // Вводим num1
        do {
            std::cout << "Выберите операцию(1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
            std::cin >> Operation;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            // сохраняем значение в поле объекта
            setValue = bChecked;
            if (setValue == false) {
                std::cout << "Неверный ввод!" << std::endl;
            }
        } while (setValue == false);

        std::cout << "Введите второе число: ";
        std::cin >> B;
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');


        // Выводим результат на экран
        std::cout << "num1 + num2 = " << calc.add() << std::endl;
        std::cout << "num1 - num2 = " << calc.subtract_1_2() << std::endl;
        std::cout << "num2 - num1 = " << calc.subtract_2_1() << std::endl;
        std::cout << "num1 * num2 = " << calc.multiply() << std::endl;
        std::cout << "num1 / num2 = " << calc.divide_1_2() << std::endl;
        std::cout << "num2 / num1 = " << calc.divide_2_1() << std::endl;
        std::cout << std::endl;
        std::cout << "Для повторного продолжения нажмите - 'Y'" << std::endl;

        std::cin >> chContinue;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки

        if (chContinue != 'Y') {
            break;
        }
    }
}

