#include "bad_CreatePolygon.h"
#include "TriangleIsosceles.h"

// �������������� ����������� - ������� a � c �����, ���� A � C �����;
TTriangleIsosceles::TTriangleIsosceles(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) {
    // FSides = 3;  // ��� ����������� � ������������ ������
    FName = "�������������� �����������";  // �������������� ��������
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_a;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_A;

    // �������� - ����� ����� ������ ���� ����� 180    
    if (!(FAngle_A + FAngle_B + FAngle_C == 180)) {
        throw bad_CreatePolygon("������ �������� ������. �������: ����� ����� �� ����� 180. " + GetName() + ")");
    }
}


