#include "bad_CreatePolygon.h"
#include "TriangleEquilateral.h"


// �������������� ����������� - ��� ������� �����, ��� ���� ����� 60;
TTriangleEquilateral::TTriangleEquilateral(int ALength_a, bool Checked) :
    TTriangleIsosceles(ALength_a, ALength_a, 60, 60, false)
{
    FName = "�������������� �����������";  // �������������� ��������

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

