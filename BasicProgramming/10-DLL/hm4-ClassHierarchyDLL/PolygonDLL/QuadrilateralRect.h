#pragma once
#include "Quadrilateral.h"

// Прямоугольник
class TQuadrilateralRect : public TQuadrilateral {
public:
    POLYGON_API TQuadrilateralRect(int ALength_a, int ALength_b);
};