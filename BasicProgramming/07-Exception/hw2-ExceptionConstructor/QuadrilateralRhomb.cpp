#include "bad_CreatePolygon.h"
#include "QuadrilateralRhomb.h"

// Ромб
TQuadrilateralRhomb::TQuadrilateralRhomb(int ALength_a, int AAngle_A, int AAngle_B) {
    // FSides = 4;  // уже инициирован в родительском классе
    FName = "Ромб";  // Переопределяем название
    FLength_a = ALength_a;
    FLength_b = ALength_a;
    FLength_c = ALength_a;
    FLength_d = ALength_a;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_A;
    FAngle_D = AAngle_B;

    // Проверка - сумма углов должна быть равна 360    
    if (!(FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360)) {
        throw bad_CreatePolygon("Ошибка создания фигуры. Причина: сумма углов не равна 360. ( " + GetName() + " )");
    }
}

