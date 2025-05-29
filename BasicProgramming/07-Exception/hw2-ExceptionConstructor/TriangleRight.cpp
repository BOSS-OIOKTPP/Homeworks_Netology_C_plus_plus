#include "bad_CreatePolygon.h"
#include "TriangleRight.h"

// ������������� ����������� - ���� C ������ ����� 90;
TTriangleRight::TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B, bool Checked) :
    TTriangle(ALength_a, ALength_b, ALength_c, AAngle_A, AAngle_B, 90, false)  
{
    FName = "������������� �����������";  // �������������� ��������

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

