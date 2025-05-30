#include "bad_CreatePolygon.h"
#include "TriangleEquilateral.h"


// �������������� ����������� - ��� ������� �����, ��� ���� ����� 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a) {
    // FSides = 3;  // ��� ����������� � ������������ ������
    FName = "�������������� �����������";  // �������������� ��������
    FLength_a = ALength_a;
    FLength_b = ALength_a;
    FLength_c = ALength_a;
    FAngle_A = 60;
    FAngle_B = 60;
    FAngle_C = 60;

    // �������� - ����� ����� ������ ���� ����� 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) {
        throw bad_CreatePolygon("������ �������� ������. �������: ����� ����� �� ����� 180. " + GetName() + ")");
    }
}

