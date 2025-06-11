#pragma once

#include "TriangleIsosceles.h"

// Равносторонний треугольник - все стороны равны, все углы равны 60;
class TTriangleEquilateral : public TTriangleIsosceles {
public:
    POLYGON_API TTriangleEquilateral(int ALength_a);
};