#pragma once
#include "Triangle.h"

// Равнобедренный треугольник - стороны a и c равны, углы A и C равны;
class TTriangleIsosceles : public TTriangle {
public:
	TTriangleIsosceles(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B);
};


