#include "QuadrilateralParallelogram.h"

// Параллелограмм
TQuadrilateralParallelogram::TQuadrilateralParallelogram(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) :
    TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, AAngle_A, AAngle_B, AAngle_A, AAngle_B)
{
    FName = "Параллелограмм";  // Переопределяем название
}
