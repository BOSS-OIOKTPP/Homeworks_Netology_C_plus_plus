#include "bad_CreatePolygon.h"
#include "QuadrilateralParallelogram.h"

// ��������������
TQuadrilateralParallelogram::TQuadrilateralParallelogram(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) {
    // FSides = 4;  // ��� ����������� � ������������ ������
    FName = "��������������";  // �������������� ��������
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_a;
    FLength_d = ALength_b;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_A;
    FAngle_D = AAngle_B;

    // �������� - ����� ����� ������ ���� ����� 180    
    if (!(FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360)) {
        throw bad_CreatePolygon("������ �������� ������. �������: ����� ����� �� ����� 180. ( " + GetName() + " )");
    }
}
