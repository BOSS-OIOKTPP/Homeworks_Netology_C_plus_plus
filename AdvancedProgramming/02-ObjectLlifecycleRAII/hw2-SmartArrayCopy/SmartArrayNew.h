#pragma once

//#include <iostream>
//#include <stdexcept>
#include <string>

class SmartArray {
private:
    int* FData;             // Указатель на массив
    int FActualSize;        // Количество элементов под которое выделена память
    int FLogicalSize;       // Фактическое количество элементов   
public:  
    SmartArray(int size);   // Конструктор
    ~SmartArray();          // Деструктор

    int ActualSize() const;         // Количество элементов под которое выделена память
    int LogicalSize() const;        // Фактическое количество элементов   
    
    void add_element(int value);    // Добавление элемента (с динамическим расширением)

    std::string Print();            // Печать массива

    // Перегрузка оператора []
    int& operator[](int index);
    const int& operator[](int index) const;

    // Перегрузка оператора =    
    SmartArray& operator=(const SmartArray& other);
};

