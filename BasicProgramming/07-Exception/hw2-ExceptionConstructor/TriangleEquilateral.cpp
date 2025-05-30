#include "bad_CreatePolygon.h"
#include "TriangleEquilateral.h"


// Равносторонний треугольник - все стороны равны, все углы равны 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a) {
    // FSides = 3;  // уже инициирован в родительском классе
    FName = "Равносторонний треугольник";  // Переопределяем название
    FLength_a = ALength_a;
    FLength_b = ALength_a;
    FLength_c = ALength_a;
    FAngle_A = 60;
    FAngle_B = 60;
    FAngle_C = 60;

    // Проверка - сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) {
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180. " + GetName() + ")");
    }
}

