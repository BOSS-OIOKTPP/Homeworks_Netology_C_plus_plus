#include <iostream>
#include "bad_CreatePolygon.h"
#include "Quadrilateral.h"

// Четырёхугольник
TQuadrilateral::TQuadrilateral(int ALength_a, int ALength_b, int ALength_c, int ALength_d,
    int AAngle_A, int AAngle_B, int AAngle_C, int AAngle_D) {
    FSides = 4;
    FName = "Четырёхугольник";
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FLength_d = ALength_d;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_C;
    FAngle_D = AAngle_D;

    std::string ErrText;
    if (!Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}
int TQuadrilateral::GetLength_a() { return FLength_a; }
int TQuadrilateral::GetLength_b() { return FLength_b; }
int TQuadrilateral::GetLength_c() { return FLength_c; }
int TQuadrilateral::GetLength_d() { return FLength_d; }
int TQuadrilateral::GetAngle_A() { return FAngle_A; }
int TQuadrilateral::GetAngle_B() { return FAngle_B; }
int TQuadrilateral::GetAngle_C() { return FAngle_C; }
int TQuadrilateral::GetAngle_D() { return FAngle_D; }

bool TQuadrilateral::Check(std::string& Err) {
    bool res{ FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360 };
    Err = "";
    if (!res) { Err = GetName()+". Ошибка создания фигуры. Причина: сумма углов не равна 360."; }
    return res;
}
// Печать
void TQuadrilateral::Print() {
    std::cout << GetName() + " ( " << "cтороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << " d = " << GetLength_d() << "; "
        << "углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " D = " << GetAngle_D() << " ) создан" << std::endl;
}


