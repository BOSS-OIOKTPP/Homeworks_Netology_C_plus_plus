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

    virtual void Print();
};

