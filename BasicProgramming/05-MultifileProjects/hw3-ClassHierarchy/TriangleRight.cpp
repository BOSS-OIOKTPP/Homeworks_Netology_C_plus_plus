#include "TriangleRight.h"

// ������������� ����������� - ���� C ������ ����� 90;
TTriangleRight::TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B) :
    TTriangle(ALength_a, ALength_b, ALength_c, AAngle_A, AAngle_B, 90)
{
    FName = "������������� �����������";  // �������������� ��������
}

