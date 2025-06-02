#include <iostream>
#include <windows.h>
#include <string>
#include "bad_CreatePolygon.h"
#include "Triangle.h"
#include "Quadrilateral.h"
#include "Params.h"


int main()
{
    // Устанавливаем кодировку консоли в UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    // Треугольник:
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 70
    try {
        TTriangle t1(10, 20, 30, 50, 60, 70, TTriangleType::Triangle);
        t1.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Прямоугольный треугольник :
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 90
    try {
        TTriangle t2(10, 20, 30, 50, 60, 90, TTriangleType::TriangleRight);
        t2.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Равнобедренный треугольник :
    // Стороны: a = 10 b = 20 c = 10
    // Углы : A = 50 B = 60 C = 50
    try {
        TTriangle t3(10, 20, 10, 50, 60, 50, TTriangleType::TriangleIsosceles);
        t3.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Равносторонний треугольник :
    // Стороны: a = 30 b = 30 c = 30
    // Углы : A = 60 B = 60 C = 60
    try {
        TTriangle t4(30, 30, 30, 60, 60, 60, TTriangleType::TriangleEquilateral);
        t4.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Четырёхугольник :
    // Стороны : a = 10 b = 20 c = 30 d = 40
    // Углы : A = 50 B = 60 C = 70 D = 80
    try {
        TQuadrilateral t5(10, 20, 30, 40, 50, 60, 70, 80, TQuadrilateralType::Quadrilateral);
        t5.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Прямоугольник :
    // Стороны : a = 10 b = 20 c = 10 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    try {
        TQuadrilateral t6(10, 20, 10, 20, 90, 90, 90, 90, TQuadrilateralType::QuadrilateralRect);
        t6.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Квадрат :
    // Стороны : a = 20 b = 20 c = 20 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    try {
        TQuadrilateral t7(20, 20, 20, 20, 90, 90, 90, 90, TQuadrilateralType::QuadrilateralSquare);
        t7.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Параллелограмм :
    // Стороны : a = 20 b = 30 c = 20 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    try {
        TQuadrilateral t8(20, 30, 20, 30, 30, 40, 30, 40, TQuadrilateralType::QuadrilateralParallelogram);
        t8.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Ромб :
    // Стороны : a = 30 b = 30 c = 30 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    try {
        TQuadrilateral t9(30, 30, 30, 30, 30, 40, 30, 40, TQuadrilateralType::QuadrilateralRhomb);
        t9.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    return EXIT_SUCCESS;
}
