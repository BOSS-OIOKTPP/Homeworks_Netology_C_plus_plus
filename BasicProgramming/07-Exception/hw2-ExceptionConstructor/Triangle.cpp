#include <iostream>
#include "bad_CreatePolygon.h"
#include "Triangle.h"

// Треугольник
TTriangle::TTriangle() {
    FSides = 3; 
    FName = "Треугольник";
    FLength_a = 0;
    FLength_b = 0;
    FLength_c = 0;
    FAngle_A = 0;
    FAngle_B = 0;
    FAngle_C = 0;
};
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

    // Проверка - сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) { 
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180. " + GetName() + ")");
    }
}

int TTriangle::GetLength_a() { return FLength_a; }
int TTriangle::GetLength_b() { return FLength_b; }
int TTriangle::GetLength_c() { return FLength_c; }
int TTriangle::GetAngle_A() { return FAngle_A; }
int TTriangle::GetAngle_B() { return FAngle_B; }
int TTriangle::GetAngle_C() { return FAngle_C; }

// Печать
void TTriangle::Print() {
    std::cout << GetName() + " ( " << "cтороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << "; "
         << "углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " ) создан" << std::endl;    
}


