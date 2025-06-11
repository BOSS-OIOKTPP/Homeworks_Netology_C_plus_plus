#include "QuadrilateralRhomb.h"

// Ромб
TQuadrilateralRhomb::TQuadrilateralRhomb(int ALength_a, int AAngle_A, int AAngle_B) :
        TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, AAngle_A, AAngle_B, AAngle_A, AAngle_B)
{
    FName = "Ромб";  // Переопределяем название
}

