#include <iostream>
#include "bad_CreatePolygon.h"
#include "Quadrilateral.h"
#include "Params.h"

// Четырёхугольник
TQuadrilateral::TQuadrilateral(int ALength_a, int ALength_b, int ALength_c, int ALength_d,
    int AAngle_A, int AAngle_B, int AAngle_C, int AAngle_D, TQuadrilateralType At) {
    FSides = 4;
    t = At;  // Тип четырехугольника
    switch (t) {
    case TQuadrilateralType::Quadrilateral:              FName = "Четырёхугольник"; break;
    case TQuadrilateralType::QuadrilateralRect:          FName = "Прямоугольник"; break;
    case TQuadrilateralType::QuadrilateralSquare:        FName = "Квадрат"; break;
    case TQuadrilateralType::QuadrilateralParallelogram: FName = "Параллелограмм"; break;
    case TQuadrilateralType::QuadrilateralRhomb:         FName = "Ромб"; break;
    default: throw bad_CreatePolygon("Ошибка создания фигуры. Введен неизвестный тип четырехугольника!"); break;
    }

    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FLength_d = ALength_d;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_C;
    FAngle_D = AAngle_D;

    // Общие проверки на ошибки параметров
    // Значения параметров должны быть больше 0
    if (!(FLength_a > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие a > 0. ( " + GetName() + " )"); }
    if (!(FLength_b > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие b > 0. ( " + GetName() + " )"); }
    if (!(FLength_c > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие c > 0. ( " + GetName() + " )"); }
    if (!(FLength_d > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие d > 0. ( " + GetName() + " )"); }
    if (!(FAngle_A > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие A > 0. ( " + GetName() + " )"); }
    if (!(FAngle_B > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие B > 0. ( " + GetName() + " )"); }
    if (!(FAngle_C > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие C > 0. ( " + GetName() + " )"); }
    if (!(FAngle_D > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие D > 0. ( " + GetName() + " )"); }
    // Сумма трех любых сторон четырехугольника должна быть больше длины четвертой стороны
    //if (!(FLength_a + FLength_b + FLength_c > FLength_d)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника a + b + c > d. " + GetName()); }
    //if (!(FLength_a + FLength_b + FLength_d > FLength_c)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника a + b + d > c. " + GetName()); }
    //if (!(FLength_a + FLength_c + FLength_d > FLength_b)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника a + c + d > b. " + GetName()); }
    //if (!(FLength_b + FLength_c + FLength_d > FLength_a)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника b + c + d > a. " + GetName()); }
    // Сумма углов должна быть равна 360    
    if (!(FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 360 градусов. ( " + GetName() + " )"); }

    // Проверка для конкретного четырехугольника
    switch (t) {
        // Прямоугольник
        case TQuadrilateralType::QuadrilateralRect:
            if (!(FLength_a == FLength_c &&
                  FLength_b == FLength_d &&
                  FAngle_A  == 90 &&
                  FAngle_B  == 90 &&
                  FAngle_C  == 90 &&
                  FAngle_D  == 90 )) {
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие a=c, b=d, углы A=B=C=D=90 градусов. ( " + GetName() + " )");
            }
            break;
        // Квадрат
        case TQuadrilateralType::QuadrilateralSquare:
            if (!(FLength_a == FLength_c &&
                  FLength_a == FLength_b &&
                  FLength_a == FLength_d &&
                  FAngle_A == 90 &&
                  FAngle_B == 90 &&
                  FAngle_C == 90 &&
                  FAngle_D == 90)) {
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: a=b=c=d, углы A=B=C=D=90 градусов. ( " + GetName() + " )");
            }
            break;
        // Параллелограмм
        case TQuadrilateralType::QuadrilateralParallelogram:
            if (!(FLength_a == FLength_c &&
                  FLength_b == FLength_d &&
                  FAngle_A  == FAngle_C &&
                  FAngle_B  == FAngle_D )) {
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: должно выполняться условие a=b, b=d и углы A=C, B=D. ( " + GetName() + " )");
            }
            break;
        // Ромб
        case TQuadrilateralType::QuadrilateralRhomb:
            if (!(FLength_a == FLength_c &&
                  FLength_a == FLength_b &&
                  FLength_a == FLength_d &&
                  FAngle_A == FAngle_C &&
                  FAngle_B == FAngle_D)) {
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: должно выполняться условие a=b=c=d и углы A=C, B=D. ( " + GetName() + " )");
            }
            break;
    }
}

int TQuadrilateral::GetLength_a() { return FLength_a; }
int TQuadrilateral::GetLength_b() { return FLength_b; }
int TQuadrilateral::GetLength_c() { return FLength_c; }
int TQuadrilateral::GetLength_d() { return FLength_d; }
int TQuadrilateral::GetAngle_A() { return FAngle_A; }
int TQuadrilateral::GetAngle_B() { return FAngle_B; }
int TQuadrilateral::GetAngle_C() { return FAngle_C; }
int TQuadrilateral::GetAngle_D() { return FAngle_D; }

// Печать
void TQuadrilateral::Print() {
    std::cout << GetName() + " ( " << "cтороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << " d = " << GetLength_d() << "; "
        << "углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " D = " << GetAngle_D() << " ) создан" << std::endl;
}