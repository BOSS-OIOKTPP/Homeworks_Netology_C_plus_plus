#include "bad_CreatePolygon.h"
#include "TriangleIsosceles.h"

// Равнобедренный треугольник - стороны a и c равны, углы A и C равны;
TTriangleIsosceles::TTriangleIsosceles(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) {
    // FSides = 3;  // уже инициирован в родительском классе
    FName = "Равнобедренный треугольник";  // Переопределяем название
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_a;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_A;

    // Проверка - сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) {
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180. " + GetName() + ")");
    }
}


