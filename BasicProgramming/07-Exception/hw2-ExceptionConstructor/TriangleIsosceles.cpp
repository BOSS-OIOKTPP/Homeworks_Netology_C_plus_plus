#include "bad_CreatePolygon.h"
#include "TriangleIsosceles.h"

// �������������� ����������� - ������� a � c �����, ���� A � C �����;
TTriangleIsosceles::TTriangleIsosceles(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B, bool Checked) :
    TTriangle(ALength_a, ALength_b, ALength_a, AAngle_A, AAngle_B, AAngle_A, false)
{
    FName = "�������������� �����������";  // �������������� ��������

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}


