#include "QuadrilateralSquare.h"

// Квадрат
TQuadrilateralSquare::TQuadrilateralSquare(int ALength_a) :
    TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, 90, 90, 90, 90)
{
    FName = "Квадрат";  // Переопределяем название
}

