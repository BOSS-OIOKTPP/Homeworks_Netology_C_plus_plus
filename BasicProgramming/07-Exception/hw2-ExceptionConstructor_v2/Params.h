#pragma once

// Тип треугольника
enum class TTriangleType {
    Triangle = 1,               // Треугольник
    TriangleRight,              // Прямоугольный треугольник
    TriangleIsosceles,          // Равнобедренный треугольник
    TriangleEquilateral         // Равносторонний треугольник    
};

// Тип четырехугольника
enum class TQuadrilateralType {
    Quadrilateral = 1,          // Четырёхугольник
    QuadrilateralRect,          // Прямоугольник
    QuadrilateralSquare,        // Квадрат
    QuadrilateralParallelogram, // Параллелограмм
    QuadrilateralRhomb          // Ромб    
};
