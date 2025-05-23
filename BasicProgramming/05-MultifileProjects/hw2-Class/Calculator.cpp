#include "Calculator.h"

// ����� ���������� ��������� �������� num1 � num2    
double Calculator::add() {
    return num1 + num2;
}

// ����� ��������tn ��������� ������������ num1 � num2
double Calculator::multiply() {
    return num1 * num2;
}

// ����� ���������� ��������� ��������� num2 �� num1
double Calculator::subtract_1_2() {
    return num1 - num2;
}

// ����� ���������� ��������� ��������� num1 �� num2
double Calculator::subtract_2_1() {
    return num2 - num1;
}

// ����� ���������� ��������� ������� num1 �� num2
double Calculator::divide_1_2() {
    return num1 / num2;
}

// ����� ���������� ��������� ������� num2 �� num1
double Calculator::divide_2_1() {
    return num2 / num1;
}

// ����� ������������� �������� ���� num1 ������ �������� ��������� num1 � ������, ���� �������� ��������� �� ����� 0. 
// ���������� true, ���� ��������� ��������� �������, � �������� ������ false
bool Calculator::set_num1(double num1) {
    if (num1 != 0) {
        this->num1 = num1;
        return true;
    }
    else
        return false;
};

// ����� ������������� �������� ���� num2 ������ �������� ��������� num2 � ������, ���� �������� ��������� �� ����� 0. 
// ���������� true, ���� ��������� ��������� �������, � �������� ������ false
bool Calculator::set_num2(double num2) {
    if (num2 != 0) {
        this->num2 = num2;
        return true;
    }
    else
        return false;
};

