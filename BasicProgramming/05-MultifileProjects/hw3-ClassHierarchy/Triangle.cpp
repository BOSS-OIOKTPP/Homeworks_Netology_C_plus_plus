#include <iostream>
#include "Triangle.h"

// Треугольник
TTriangle::TTriangle(int ALength_a, int ALength_b, int ALength_c,
        int AAngle_A, int AAngle_B, int AAngle_C) {
    FSides = 3;
    FName = "Треугольник";
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_C;
}
int TTriangle::GetLength_a() { return FLength_a; }
int TTriangle::GetLength_b() { return FLength_b; }
int TTriangle::GetLength_c() { return FLength_c; }
int TTriangle::GetAngle_A() { return FAngle_A; }
int TTriangle::GetAngle_B() { return FAngle_B; }
int TTriangle::GetAngle_C() { return FAngle_C; }

void TTriangle::Print() {
    std::cout << GetName() + " :" << std::endl;
    std::cout << "Стороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << std::endl;
    std::cout << "Углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << std::endl;
    std::cout << std::endl;
}


