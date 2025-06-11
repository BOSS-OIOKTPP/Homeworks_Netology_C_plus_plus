#pragma once

#ifdef POLYGONDLL_EXPORTS
    #define POLYGON_API __declspec(dllexport)
#else
    #define POLYGON_API __declspec(dllimport)
#endif

#include <string>

// Базовый класс
class TPolygon {
protected:
    int FSides;         // Количество сторон
    std::string FName;  // Названия фигуры
public:
    POLYGON_API TPolygon();

    POLYGON_API int GetSides();
    POLYGON_API std::string GetName();

    POLYGON_API virtual void Print();
};

