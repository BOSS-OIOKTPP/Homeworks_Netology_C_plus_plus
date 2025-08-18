#include "SmartArray.h"

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
int SmartArray::ActualSize() { 
    return FActualSize;
}
// Фактическое количество элементов   
int SmartArray::LogicalSize() {
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

// Перегрузка оператора [] для удобства
int& SmartArray::operator[](int index) {
    if (index >= FActualSize) {
        throw std::out_of_range("Index out of range");
    }
    return FData[index];
}
const int& SmartArray::operator[](int index) const {
    return operator[](index); // Вызываем неконстантную версию
}