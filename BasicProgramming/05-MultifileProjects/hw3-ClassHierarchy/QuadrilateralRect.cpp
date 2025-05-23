#include "QuadrilateralRect.h"

// Прямоугольник
TQuadrilateralRect::TQuadrilateralRect(int ALength_a, int ALength_b) :
    TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, 90, 90, 90, 90)
{
    FName = "Прямоугольник";  // Переопределяем название
}
