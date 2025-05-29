#include "bad_CreatePolygon.h"
#include "QuadrilateralParallelogram.h"

// Параллелограмм
TQuadrilateralParallelogram::TQuadrilateralParallelogram(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B, bool Checked) :
    TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, AAngle_A, AAngle_B, AAngle_A, AAngle_B,false)
{
    FName = "Параллелограмм";  // Переопределяем название

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}
