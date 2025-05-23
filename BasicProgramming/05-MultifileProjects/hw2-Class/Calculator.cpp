#include "Calculator.h"

// Метод возвращает результат сложения num1 и num2    
double Calculator::add() {
    return num1 + num2;
}

// Метод возвращаtn результат перемножения num1 и num2
double Calculator::multiply() {
    return num1 * num2;
}

// Метод возвращает результат вычитания num2 из num1
double Calculator::subtract_1_2() {
    return num1 - num2;
}

// Метод возвращает результат вычитания num1 из num2
double Calculator::subtract_2_1() {
    return num2 - num1;
}

// Метод возвращает результат деления num1 на num2
double Calculator::divide_1_2() {
    return num1 / num2;
}

// Метод возвращает результат деления num2 на num1
double Calculator::divide_2_1() {
    return num2 / num1;
}

// Метод устанавливает значение поля num1 равное значению аргумента num1 в случае, если значение аргумента не равно 0. 
// Возвращает true, если установка произошла успешно, в обратном случае false
bool Calculator::set_num1(double num1) {
    if (num1 != 0) {
        this->num1 = num1;
        return true;
    }
    else
        return false;
};

// Метод устанавливает значение поля num2 равное значению аргумента num2 в случае, если значение аргумента не равно 0. 
// Возвращает true, если установка произошла успешно, в обратном случае false
bool Calculator::set_num2(double num2) {
    if (num2 != 0) {
        this->num2 = num2;
        return true;
    }
    else
        return false;
};

