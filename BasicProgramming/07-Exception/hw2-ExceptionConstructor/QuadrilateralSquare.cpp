#include "bad_CreatePolygon.h"
#include "QuadrilateralSquare.h"

// Квадрат
TQuadrilateralSquare::TQuadrilateralSquare(int ALength_a, bool Checked) :
    TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, 90, 90, 90, 90, false)
{
    FName = "Квадрат";  // Переопределяем название

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

