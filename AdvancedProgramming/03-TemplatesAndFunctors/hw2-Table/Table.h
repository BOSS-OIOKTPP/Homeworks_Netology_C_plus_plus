#pragma once
#include "Array.h"

template<typename T>
class Table {
private:
    Array<T>** FData;       // Указатель на массив
    int FRows;              // Количество строк
    int FCols;              // Количество столбцов    
public:
    // Конструктор
    Table(int rows, int cols) {
        FRows = rows;
        FCols = cols;
        FData = new Array<T>*[rows];
        for (int i = 0; i < rows; ++i) {
            FData[i] = new Array<T>(cols);
        }
    }
    
    // Конструктор копирования
    Table(const Table& other) : FData(nullptr), FRows(0), FCols(0) {
        *this = other;   // используем перегрузку оператора =
    }
    
    // Деструктор
    ~Table() {  
        for (int i = 0; i < FRows; ++i) {
            delete FData[i];  
        }        
        delete[] FData;
    }

    // Количество строк
    int Rows() const { return FRows; }
    // Количество столбцов
    int Cols() const { return FCols; }        

    // Размер массивав
    const int Size() const {
        return FRows * FCols;
    }
    
    // Перегрузка оператора []
    Array<T>& operator[](int row) {
        if (row < 0 || row >= FRows) {
            throw std::out_of_range(
                "Индекс строки " + std::to_string(row) +
                " выходит за границу [0; " + std::to_string(FRows - 1) + "]"
            );
        }
        return *FData[row];
    }
    // Перегрузка const оператора []
    const Array<T>& operator[](int index) const {
        return operator[](index); // Вызываем неконстантную версию
    }

    // Перегрузка оператора =    
    Table& operator=(const Table& other) {        
        if (this != &other) { // Проверка на самоприсваивание
            // Освобождаем текущие ресурсы
            for (int i = 0; i < FRows; ++i) {
                delete FData[i];  
            }
            delete[] FData;            

            // Копируем данные из другого объекта
            FRows = other.FRows;
            FCols = other.FCols;
            FData = new Array<T>*[FRows];
            // Создаем новые строки
            for (int i = 0; i < FRows; ++i) {
                FData[i] = new Array<T>(FCols);
            }
            // Копируем элементы
            for (int i = 0; i < FRows; ++i) {
                for (int j = 0; j < FCols; ++j) {
                    (*FData[i])[j] = (*other.FData[i])[j];
                }
            }
        }
        return *this;
    }

    // Печать массива     
    void Print() {
        for (int i = 0; i < FRows; ++i) 
            std::cout << FData[i]->Print() << std::endl;

    }; 
};
