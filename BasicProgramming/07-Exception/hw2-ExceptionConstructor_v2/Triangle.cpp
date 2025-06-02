#include <iostream>
#include "bad_CreatePolygon.h"
#include "Triangle.h"
#include "Params.h"

// Треугольник
TTriangle::TTriangle(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B, int AAngle_C, TTriangleType At) {
    FSides = 3;
    t=At;  // Тип треугольника
    switch (t) {
        case TTriangleType::Triangle :           FName = "Треугольник"; break;
        case TTriangleType::TriangleRight:       FName = "Прямоугольный треугольник"; break;
        case TTriangleType::TriangleIsosceles:   FName = "Равнобедренный треугольник"; break;
        case TTriangleType::TriangleEquilateral: FName = "Равносторонний треугольник"; break;
        default: throw bad_CreatePolygon("Ошибка создания фигуры. Введен неизвестный тип треугольника!"); break;
    }
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_C;

    // Общие проверки на ошибки параметров
    // Значения параметров должны быть больше 0
    if (!(FLength_a > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие a > 0. ( " + GetName() + " )"); }
    if (!(FLength_b > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие b > 0. ( " + GetName() + " )"); }
    if (!(FLength_c > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие c > 0. ( " + GetName() + " )"); }
    if (!(FAngle_A > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие A > 0. ( " + GetName() + " )"); }
    if (!(FAngle_B > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие B > 0. ( " + GetName() + " )"); }
    if (!(FAngle_C > 0)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие C > 0. ( " + GetName() + " )"); }
    // Сумма двух любых сторон треугольника должна быть больше длины третьей стороны
    //if (!(FLength_a + FLength_b > FLength_c)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника a + b > c. " + GetName()); }
    //if (!(FLength_b + FLength_c > FLength_a)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника b + c > a. " + GetName()); }
    //if (!(FLength_b + FLength_c > FLength_a)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие для треугольника c + a > b. " + GetName()); }
    // Сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) { throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180 градусов. ( " + GetName() + " )"); }

    // Проверка для конкретного треугольника
    switch (t) {
        // Прямоугольный треугольник
        case TTriangleType::TriangleRight:       
            if (!(FAngle_C == 90)) { 
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: не выполняется условие C = 90 градусов. ( " + GetName() + " )"); }
            break;
        // Равнобедренный треугольник
        case TTriangleType::TriangleIsosceles:   
            if (!(FLength_a == FLength_c && FAngle_A== FAngle_C)) { 
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: должно выполняться условие a=c и A=C. ( " + GetName() + " )"); }
            break;
        // Равносторонний треугольник
        case TTriangleType::TriangleEquilateral: 
            if (!(FLength_a == FLength_b &&
                  FLength_a == FLength_c && 
                  FAngle_A  == 60 && 
                  FAngle_B  == 60 && 
                  FAngle_C  == 60)) { 
                throw bad_CreatePolygon("Ошибка создания фигуры. Причина: должно выполняться условие a=b=c и A=B=C=60. ( " + GetName() + " )"); }
            break;
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


