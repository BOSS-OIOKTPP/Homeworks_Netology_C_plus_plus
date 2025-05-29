#include <iostream>
#include <locale>
#include <string>
#include "bad_CreatePolygon.h"
#include "Triangle.h"
#include "TriangleRight.h"
#include "TriangleIsosceles.h"
#include "TriangleEquilateral.h"
#include "Quadrilateral.h"
#include "QuadrilateralRect.h"
#include "QuadrilateralSquare.h"
#include "QuadrilateralParallelogram.h"
#include "QuadrilateralRhomb.h"


int main()
{
    setlocale(LC_ALL, "russian");

    // Треугольник:
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 70
    try {
        TTriangle t1(10, 20, 30, 50, 60, 70);
        t1.Print(); }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Прямоугольный треугольник :
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 90
    try {
        TTriangleRight t2(10, 20, 30, 50, 60);
        t2.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }
    
    // Равнобедренный треугольник :
    // Стороны: a = 10 b = 20 c = 10
    // Углы : A = 50 B = 60 C = 50
    try {
        TTriangleIsosceles t3(10, 20, 50, 60);
        t3.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Равносторонний треугольник :
    // Стороны: a = 30 b = 30 c = 30
    // Углы : A = 60 B = 60 C = 60
    try {
        TTriangleEquilateral t4(30);
        t4.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Четырёхугольник :
    // Стороны : a = 10 b = 20 c = 30 d = 40
    // Углы : A = 50 B = 60 C = 70 D = 80
    try {
        TQuadrilateral t5(10, 20, 30, 40, 50, 60, 70, 80);
        t5.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }
    
    // Прямоугольник :
    // Стороны : a = 10 b = 20 c = 10 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    try {
        TQuadrilateralRect t6(10, 20);
        t6.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }

    // Квадрат :
    // Стороны : a = 20 b = 20 c = 20 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    try {
        TQuadrilateralSquare t7(20);
        t7.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }
    
    // Параллелограмм :
    // Стороны : a = 20 b = 30 c = 20 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    try {
        TQuadrilateralParallelogram t8(20, 30, 30, 40);
        t8.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }
    
    // Ромб :
    // Стороны : a = 30 b = 30 c = 30 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    try {
        TQuadrilateralRhomb t9(30, 30, 40);
        t9.Print();
    }
    catch (const bad_CreatePolygon& ex) { std::cout << ex.what() << std::endl; }
    
    return 0;
}
