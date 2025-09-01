#include <iostream>
#include <string>
#include <windows.h>
#include <sstream>
#include "SmartArrayNew2.h"

// Функтор для подсчета чисел, делящихся на 3
class DivByThreeAndCount {
private:
    int sum;
    int count;
public:
    DivByThreeAndCount(): sum(0), count(0) {}

    void operator()(int value) {
        if (value % 3 == 0) {
            sum += value;
            count++;
        }
    }

    int get_sum() const {
        return sum;
    }

    int get_count() const {
        return count;
    }
};


// Шаблон
template<typename T>
T& square(T& value) {    
    return value *= value; 
}
// Специализация
template<>
SmartArray& square(SmartArray& arr) {
    for (int i = 0; i < arr.LogicalSize(); ++i)
        arr[i] *= arr[i];  
    return arr;
}

// Меню для выбора действия
int exit_program() {
    int intReplay;

    while (true) {
        std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "1. Повторить ввод?" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        std::cout << "Напишите цифру: ";

        std::cin >> intReplay;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intReplay >= 1 && intReplay <= 2) 
            break;        
    }
    return intReplay;
}


// Пример использования
int main() {

    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    while (true) {
        std::string input;      // Строка входных данных
        SmartArray numbers(10); // Используем динамический массив из предыдущей домашней работы для хранения чисел        
        int number;             // Число в строке

        // Очищаем консоль 
        system("cls");

        // Меню
        std::cout << "Программа по теме шаблоны ""Счётчик чисел""" << std::endl;
        std::cout << "Введите числа, отделяя их пробелами, для выхода введите exit" << std::endl;        

        std::cout << "[IN]: ";

        // Чтение всей строки
        if (!std::getline(std::cin >> std::ws, input)) {
            // Ошибка ввода (например, Ctrl+Z/Ctrl+D)
            std::cin.clear(); // Сброс флагов ошибок
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            std::cout << "Ошибка ввода! Попробуйте снова." << std::endl;

            continue;
        }
        
        // Выходим из приложения
        if (input == "exit") 
            break;
        
        // Создаем поток из строки и заполняем массив        
        std::stringstream ss(input);
        while (ss >> number) 
            numbers.add_element(number);        

        // Проверяем, были ли ошибки 
        std::string err;
        err = "";        
        if (ss.fail() && !ss.eof()) {
            ss.clear(); // Очищаем флаги ошибок

            // Строка с ошибкой
            std::string bad_input;
            ss >> bad_input;
            err = "Ошибка ввода! Некорректная строка чисел: '" + bad_input + "'";            
        }
        // ошибки будем выводить по очереди
        if (err=="" && numbers.LogicalSize() == 0)
            err = "Ошибка ввода! Не введено ни одного числа.";
        
        // Если есть ошибки то
        if (err != "") {  
            std::cout << err;

            // Выполняем повторно ввод
            if (exit_program() == 1) { 
                numbers.Clear();
                continue;
            }
            // Прерываем программу
            else {
                break;               
            }
        }



        //**************************************//
        //  Выводим результат работы программы  //
        //**************************************//


        // Используем функтор для подсчета чисел, делящихся на 3
        DivByThreeAndCount divByThreeAndCount;
        for (int i = 0; i < numbers.LogicalSize(); ++i) {
            divByThreeAndCount(numbers[i]);
        }

        std::cout << "[OUT]: get_sum() = " << divByThreeAndCount.get_sum() << std::endl;
        std::cout << "[OUT]: get_count() = " << divByThreeAndCount.get_count() << std::endl;



        //**************************************//




        // Выполняем повторно ввод
        if (exit_program() == 1) {
            numbers.Clear();
            continue;
        }
        // Прерываем программу
        else {
            break;
        }
    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
