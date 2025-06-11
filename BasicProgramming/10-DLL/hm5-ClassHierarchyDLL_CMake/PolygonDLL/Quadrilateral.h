#pragma once
#include "Polygon.h"

// Четырёхугольник
class TQuadrilateral : public TPolygon {
private:
    int FLength_a;
    int FLength_b;
    int FLength_c;
    int FLength_d;
    int FAngle_A;
    int FAngle_B;
    int FAngle_C;
    int FAngle_D;
public:
    POLYGON_API TQuadrilateral(int ALength_a, int ALength_b, int ALength_c, int ALength_d,
        int AAngle_A, int AAngle_B, int AAngle_C, int AAngle_D);
    POLYGON_API int GetLength_a();
    POLYGON_API int GetLength_b();
    POLYGON_API int GetLength_c();
    POLYGON_API int GetLength_d();
    POLYGON_API int GetAngle_A();
    POLYGON_API int GetAngle_B();
    POLYGON_API int GetAngle_C();
    POLYGON_API int GetAngle_D();

    POLYGON_API void Print() override;
};

