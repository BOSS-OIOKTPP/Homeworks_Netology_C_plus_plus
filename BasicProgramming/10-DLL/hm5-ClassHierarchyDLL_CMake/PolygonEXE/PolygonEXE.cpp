#include <iostream>
#include <windows.h>
#include <string>
#include "Triangle.h"
#include "TriangleRight.h"
#include "TriangleIsosceles.h"
#include "TriangleEquilateral.h"
#include "Quadrilateral.h"
#include "QuadrilateralRect.h"
#include "QuadrilateralSquare.h"
#include "QuadrilateralParallelogram.h"
#include "QuadrilateralRhomb.h"

// Печать
void Print_Info(TPolygon& P) {
    P.Print();
}


int main()
{
    //setlocale(LC_ALL, "russian");

    // Устанавливаем кодировку консоли
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);


    // Треугольник:
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 70
    TTriangle t1(10, 20, 30, 50, 60, 70);

    // Прямоугольный треугольник :
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 90
    TTriangleRight t2(10, 20, 30, 50, 60);

    // Равнобедренный треугольник :
    // Стороны: a = 10 b = 20 c = 10
    // Углы : A = 50 B = 60 C = 50
    TTriangleIsosceles t3(10, 20, 50, 60);

    // Равносторонний треугольник :
    // Стороны: a = 30 b = 30 c = 30
    // Углы : A = 60 B = 60 C = 60
    TTriangleEquilateral t4(30);

    // Четырёхугольник :
    // Стороны : a = 10 b = 20 c = 30 d = 40
    // Углы : A = 50 B = 60 C = 70 D = 80
    TQuadrilateral t5(10, 20, 30, 40, 50, 60, 70, 80);

    // Прямоугольник :
    // Стороны : a = 10 b = 20 c = 10 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    TQuadrilateralRect t6(10, 20);

    // Квадрат :
    // Стороны : a = 20 b = 20 c = 20 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    TQuadrilateralSquare t7(20);

    // Параллелограмм :
    // Стороны : a = 20 b = 30 c = 20 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    TQuadrilateralParallelogram t8(20, 30, 30, 40);

    // Ромб :
    // Стороны : a = 30 b = 30 c = 30 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    TQuadrilateralRhomb t9(30, 30, 40);


    Print_Info(t1);
    Print_Info(t2);
    Print_Info(t3);
    Print_Info(t4);
    Print_Info(t5);
    Print_Info(t6);
    Print_Info(t7);
    Print_Info(t8);
    Print_Info(t9);


    system("pause");

    return EXIT_SUCCESS;
}
