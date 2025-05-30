#include "bad_CreatePolygon.h"
#include "TriangleRight.h"

// Прямоугольный треугольник - угол C всегда равен 90;
TTriangleRight::TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B)  {
    // FSides = 3;  // уже инициирован в родительском классе
    FName = "Прямоугольный треугольник";
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = 90;

    // Проверка - сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) {
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180. " + GetName() + ")");
    }    
}

