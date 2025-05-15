// Задача 1. Калькулятор двух чисел
// В этом задании вам нужно будет создать класс, выполняющий простые арифметические операции для двух чисел, и продемонстрировать его работу
//
// Создайте класс Calculator. Класс должен содержать два поля num1 и num2 для хранения дробных чисел.Также класс должен содержать следующие методы :
//
// double add() - метод должен возвращать результат сложения num1 и num2
// double multiply() - метод должен возвращать результат перемножения num1 и num2
// double subtract_1_2() - метод должен возвращать результат вычитания num2 из num1
// double subtract_2_1() - метод должен возвращать результат вычитания num1 из num2
// double divide_1_2() - метод должен возвращать результат деления num1 на num2
// double divide_2_1() - метод должен возвращать результат деления num2 на num1
// bool set_num1(double num1) - метод должен установить значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
// bool set_num2(double num2) - метод должен установить значение поля num2 равное значению аргумента num2 в случае, если значение аргумента не равно 0. Возвращает true, если установка произошла успешно, в обратном случае false
// Напишите код, демонстрирующий работу класса Calculator.Попросите пользователя ввести два числа.После этого выведите пользователю результаты всех операций или попросите его ввести значение ещё раз, если предыдущий ввод был некорректен
//
// Программа спрашивает пользователя бесконечно, пока он сам не закроет консоль
//
// Пример работы программы
// Консоль
// Введите num1 : 3
// Введите num2 : 6
// num1 + num2 = 9
// num1 - num2 = -3
// num2 - num1 = 3
// num1 * num2 = 18
// num1 / num2 = 0.5
// num2 / num1 = 2
// Введите num1 : 5
// Введите num2 : 0
// Неверный ввод!
// Введите num2 : 5
// num1 + num2 = 10
// num1 - num2 = 0
// num2 - num1 = 0
// num1 * num2 = 25
// num1 / num2 = 1
// num2 / num1 = 1



#include <iostream>
#include <locale>
#include <string>

class Calculator {
private:
    double num1;
    double num2;
public:    
    // Метод возвращает результат сложения num1 и num2    
    double add() { 
        return num1 + num2; 
    }
    // Метод возвращаtn результат перемножения num1 и num2
    double multiply() { 
        return num1 * num2; 
    }
    // Метод возвращает результат вычитания num2 из num1
    double subtract_1_2() { 
        return num1 - num2; 
    }   
    // Метод возвращает результат вычитания num1 из num2
    double subtract_2_1() {
        return num2 - num1;
    }
    // Метод возвращает результат деления num1 на num2
    double divide_1_2() {
        return num1/num2;
    }       
    // Метод возвращает результат деления num2 на num1
    double divide_2_1() {
        return num2 / num1;
    }
    // Метод устанавливает значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. 
    // Возвращает true, если установка произошла успешно, в обратном случае false
    bool set_num1(double num1) {
        if (num1 != 0) {
            this->num1 = num1;
            return true;
        }
        else
            return false;
    };
    // Метод устанавливает значение поля num2 равное значению аргумента num2 в случае, если значение аргумента не равно 0. 
    // Возвращает true, если установка произошла успешно, в обратном случае false
    bool set_num2(double num2) {
        if (num2 != 0) {
            this->num2 = num2;
            return true;
        }
        else
            return false;
    };
};

int main()
{
    setlocale(LC_ALL, "russian");

    char chContinue{'Y'};
    double num1{ 0.0 };
    double num2{ 0.0 };

    Calculator calc;
    bool setValue{true};

    while (true) {
        system("cls");  // Очищаем консоль

        // Вводим num1
        do {
            std::cout << "Введите num1 : ";
            std::cin >> num1;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки
            // сохраняем значение в поле объекта
            setValue = calc.set_num1(num1);
            if  (setValue==false) {
                std::cout << "Неверный ввод!" << std::endl;
            }
        } while (setValue == false);

        // Вводим num2
        do {
            std::cout << "Введите num2 : ";
            std::cin >> num2;
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
        std::cout << "Для повторного продолжения нажмите - 'Y'"  << std::endl;
        
        std::cin >> chContinue;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очищаем буфер до символа новой строки
        
        if (chContinue != 'Y') {
            break;
        }        
    }
    return 0;
}
