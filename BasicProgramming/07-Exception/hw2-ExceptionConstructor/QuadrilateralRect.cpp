#include "bad_CreatePolygon.h"
#include "QuadrilateralRect.h"

// Прямоугольник
TQuadrilateralRect::TQuadrilateralRect(int ALength_a, int ALength_b, bool Checked) :
    TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, 90, 90, 90, 90, false)
{
    FName = "Прямоугольник";  // Переопределяем название

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}
