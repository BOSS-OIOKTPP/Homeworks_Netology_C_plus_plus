#pragma once
#include "Polygon.h"

// Четырёхугольник
class TQuadrilateral : public TPolygon {
protected:
    int FLength_a;
    int FLength_b;
    int FLength_c;
    int FLength_d;
    int FAngle_A;
    int FAngle_B;
    int FAngle_C;
    int FAngle_D;
public:
    TQuadrilateral();
    TQuadrilateral(int ALength_a, int ALength_b, int ALength_c, int ALength_d,
        int AAngle_A, int AAngle_B, int AAngle_C, int AAngle_D);
    int GetLength_a();
    int GetLength_b();
    int GetLength_c();
    int GetLength_d();
    int GetAngle_A();
    int GetAngle_B();
    int GetAngle_C();
    int GetAngle_D();
    // Печать
    void Print() override;
};

