#pragma once
#include "Triangle.h"

// Прямоугольный треугольник - угол C всегда равен 90;
class TTriangleRight : public TTriangle {
public:
    TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B);
};

