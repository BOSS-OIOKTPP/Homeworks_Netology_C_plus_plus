#pragma once
#include "Polygon.h"
#include <string>

// Треугольник
class TTriangle : public TPolygon {
protected:
    int FLength_a;
    int FLength_b;
    int FLength_c;
    int FAngle_A;
    int FAngle_B;
    int FAngle_C;
public:
    TTriangle(int ALength_a, int ALength_b, int ALength_c,
        int AAngle_A, int AAngle_B, int AAngle_C);

    int GetLength_a();
    int GetLength_b();
    int GetLength_c();
    int GetAngle_A();
    int GetAngle_B();
    int GetAngle_C();

    // Проверка параметров треугольника
    bool Check(std::string& Err) override;
    // Печать
    void Print() override;
};