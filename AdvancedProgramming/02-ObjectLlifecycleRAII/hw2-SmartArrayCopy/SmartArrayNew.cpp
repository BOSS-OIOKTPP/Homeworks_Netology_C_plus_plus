#include <iostream>
#include <string>
#include "SmartArrayNew.h"

// Конструктор
SmartArray::SmartArray(int size) {
    FActualSize = size;
    FLogicalSize = 0;
    FData = new int[size];
}
// Деструктор
SmartArray::~SmartArray() {
    delete[] FData;
}
// Количество элементов под которое выделена память
int SmartArray::ActualSize() const { 
    return FActualSize;
}
// Фактическое количество элементов   
int SmartArray::LogicalSize() const {
    return FLogicalSize;
}
// Добавление элемента (с динамическим расширением)
void SmartArray::add_element(int value) {
    // создаем массив в 2 раза больше чем был и копируем в него данные из первово массива
    if (FLogicalSize == FActualSize) {
        int* tmpArray = new int[2 * FActualSize];
        for (int i = 0; i < FActualSize; ++i)
            tmpArray[i] = FData[i];
        // удаляем старый массив
        delete[] FData;
        // запоминаем ссылку на новый массив
        FData = tmpArray;
        // увеличиваем фактический размер в 2 раза
        FActualSize *= 2;
    }

    // увеличиваем логический размер на 1
    FLogicalSize++;
    // запоминаем введенное значение
    FData[FLogicalSize-1] = value;    
}

// Печать массива
std::string SmartArray::Print() {
    std::string str;
    str = "";
    for (int i = 0; i < FLogicalSize; ++i)              
        str += std::to_string(FData[i]) + " ";
    for (int i = FLogicalSize; i < FActualSize; ++i)
        str += "_ ";
    return str;
}

// Перегрузка оператора [] 
int& SmartArray::operator[](int index) {
    if (index >= FLogicalSize) {
        //throw std::out_of_range("Index out of range");
        throw std::out_of_range(
            "Индекс массива SmartArray[" + std::to_string(index) + "]"
            " выходит за границу (Фактический размер [0; " + std::to_string(FLogicalSize-1) + "])"
        );
    }
    return FData[index];
}
const int& SmartArray::operator[](int index) const {
    return operator[](index); // Вызываем неконстантную версию
}

// Перегрузка оператора = 
SmartArray& SmartArray::operator=(const SmartArray& other) {
    if (this != &other) { // Проверка на самоприсваивание
        // Освобождаем текущие ресурсы
        delete[] FData;

        // Копируем данные из другого объекта
        FActualSize = other.FActualSize;
        FLogicalSize = other.FLogicalSize;
        FData = new int[FActualSize];

        // Копируем элементы массива
        for (int i = 0; i < FLogicalSize; ++i) {
            FData[i] = other.FData[i];
        }
    }
    return *this;
}


// НЕПРАВИЛЬНЫЙ ВАРИАНТ
//SmartArray& SmartArray::operator=(const SmartArray& other) {
//    if (this != &other) { // Проверка на самоприсваивание
//        if (FLogicalSize < other.FLogicalSize) {
//            // Уравниваем количество элементов
//            for (int i = 0; i < (other.FLogicalSize - FLogicalSize); ++i) 
//                this->add_element(0);
//        }
//
//        // Выполняем копирование из одного массива в другой
//        for (int i = 0; i < other.FLogicalSize; ++i)
//            FData[i] = other.FData[i];
//    }
//    return *this;
//}