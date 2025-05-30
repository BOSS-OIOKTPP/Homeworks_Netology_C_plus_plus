#include "bad_CreatePolygon.h"
#include "QuadrilateralRect.h"

// Прямоугольник
TQuadrilateralRect::TQuadrilateralRect(int ALength_a, int ALength_b, bool Checked) {
    // FSides = 4;  // уже инициирован в родительском классе
    FName = "Прямоугольник";  // Переопределяем название
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_a;
    FLength_d = ALength_b;
    FAngle_A = 90;
    FAngle_B = 90;
    FAngle_C = 90;
    FAngle_D = 90;    

    // Проверка - сумма углов должна быть равна 180    
    if (!(FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360)) {
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 180. ( " + GetName() + " )");
    }
}
