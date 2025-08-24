#pragma once

#include <iostream>
#include <stdexcept>

class SmartArray {
private:
    int* FData;             // Указатель на массив
    int FActualSize;        // Количество элементов под которое выделена память
    int FLogicalSize;       // Фактическое количество элементов   
public:  
    SmartArray(int size);   // Конструктор
    ~SmartArray();          // Деструктор

    int ActualSize();       // Количество элементов под которое выделена память
    int LogicalSize();      // Фактическое количество элементов   
    
    void add_element(int value); // Добавление элемента (с динамическим расширением)

    // Перегрузка оператора [] для удобства
    int& operator[](int index);
    const int& operator[](int index) const;
};

