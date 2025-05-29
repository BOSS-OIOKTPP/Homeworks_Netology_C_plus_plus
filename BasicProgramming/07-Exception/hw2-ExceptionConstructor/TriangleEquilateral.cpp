#include "bad_CreatePolygon.h"
#include "TriangleEquilateral.h"


// Равносторонний треугольник - все стороны равны, все углы равны 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a, bool Checked) :
    TTriangleIsosceles(ALength_a, ALength_a, 60, 60, false)
{
    FName = "Равносторонний треугольник";  // Переопределяем название

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

