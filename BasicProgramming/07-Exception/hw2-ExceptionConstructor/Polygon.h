#pragma once
#include <string>

// Базовый класс
class TPolygon {
protected:
    int FSides;         // Количество сторон
    std::string FName;  // Названия фигуры
public:
    TPolygon();

    int GetSides();
    std::string GetName();

    // Проверка 
    virtual bool Check(std::string& Err);
    // Печать
    virtual void Print();
};

