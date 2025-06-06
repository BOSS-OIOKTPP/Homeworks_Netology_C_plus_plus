#include "TriangleEquilateral.h"

// Равносторонний треугольник - все стороны равны, все углы равны 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a) :
    TTriangleIsosceles(ALength_a, ALength_a, 60, 60)
{
    FName = "Равносторонний треугольник";  // Переопределяем название
}

