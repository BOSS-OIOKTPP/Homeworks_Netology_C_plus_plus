// hw1-MathematicalFunctions.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
//Задача 1. Математические функции
//В этом задании вы вынесете математические функции в отдельный файл.
//
//Даны следующие математически функции : сложение, вычитание, умножение, деление, возведение в степень.
//
//Вам нужно разместить их в отдельном файле исходного кода и воспользоваться ими из функции main.
//
//Попросите пользователя ввести два числа и выбрать операцию.Выведите результат ему на консоль.
//
//Пример работы программы
//Консоль
//Введите первое число : 20
//Введите второе число : 2
//Выберите операцию(1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень) : 5
//20 в степени 2 = 400

#include <iostream>
#include <locale>
#include <string>
#include "MathFunctions.h"

class TNumPair {
private:
    int FA;          // 1 число
    int FB;          // 2 число
    int FOperation;  // номер операции над числами: 1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень
public:
    TNumPair() {
        FA = 0;
        FB = 0;
        FOperation = 0;
    }

    void SetA(int A) { FA = A; }
    int GetA() { return FA; }

    void SetB(int B) { FB = B; }
    int GetB() { return FB; }

    void SetOperation(int Operation) { FOperation = Operation; }
    int GetOperation() { return FOperation; }

    bool Checked(std::string& Err) {
        bool ch(true);
        Err = "";
        if (FOperation == 4 && FB == 0) {
             Err = "Неверный ввод!. Второе число должно быть не равно 0!";
             ch = false;
        }
        else if (FOperation == 5 && FB < 0) {
            Err = "Неверный ввод!. Второе число должно быть больше или равно 0!";
            ch = false;
        }
        else {
            Err = "Некорректный номер операции!";
            ch = false;
        }
        return ch;
    }   

    void Print() {        
        if (FOperation == 1) { std::cout << FA << " + " << FB << " = " << Add(FA, FB) << std::endl; }
        else if (FOperation == 2) { std::cout << FA << " - " << FB << " = " << Subtract(FA, FB) << std::endl; }
        else if (FOperation == 3) { std::cout << FA << " * " << FB << " = " << Multiply(FA, FB) << std::endl; }
        else if (FOperation == 4) { std::cout << FA << " / " << FB << " = " << Multiply(FA, FB) << std::endl; }
        else if (FOperation == 5) { std::cout << FA << " в степени " << FB << " = " << Power(FA, FB) << std::endl; }
    }
};



int main()
{
    setlocale(LC_ALL, "russian");

    TNumPair NumPair;
    
    int A{ 0 };
    int B{ 0 };
    int Operation{ 0 };
    std::string Err;
    bool Checked;


    bool bChecked{ true };

    while (true) {
        system("cls");  // Очищаем консоль

        // Вводим A
        std::cout << "Введите первое число: ";
        std::cin >> A;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки
        NumPair.SetA(A);

        // Вводим B
        std::cout << "Введите второе число: ";
        std::cin >> B;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
        NumPair.SetB(B);

        // Выбираем операцию
        // Вводим num1
        do {
            std::cout << "Выберите операцию (1 - сложение, 2 вычитание, 3 - умножение, 4 - деление, 5 - возведение в степень): ";
            std::cin >> Operation;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            NumPair.SetOperation(Operation);

            // сохраняем значение в поле объекта
            Checked = NumPair.Checked(Err);
            if (Checked == false) {
                std::cout << Err << std::endl;
            }
        } while (Checked == false);

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

