#pragma once
#include "Polygon.h"

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
    POLYGON_API TTriangle(int ALength_a, int ALength_b, int ALength_c,
        int AAngle_A, int AAngle_B, int AAngle_C);

    POLYGON_API int GetLength_a();
    POLYGON_API int GetLength_b();
    POLYGON_API int GetLength_c();
    POLYGON_API int GetAngle_A();
    POLYGON_API int GetAngle_B();
    POLYGON_API int GetAngle_C();

    POLYGON_API void Print() override;
};