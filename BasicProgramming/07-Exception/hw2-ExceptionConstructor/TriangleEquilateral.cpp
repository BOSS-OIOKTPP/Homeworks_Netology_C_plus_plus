#include "TriangleEquilateral.h"

// �������������� ����������� - ��� ������� �����, ��� ���� ����� 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a) :
    TTriangleIsosceles(ALength_a, ALength_a, 60, 60)
{
    FName = "�������������� �����������";  // �������������� ��������
}

