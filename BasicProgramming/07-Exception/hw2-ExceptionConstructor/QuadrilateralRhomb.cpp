#include "bad_CreatePolygon.h"
#include "QuadrilateralRhomb.h"

// ����
TQuadrilateralRhomb::TQuadrilateralRhomb(int ALength_a, int AAngle_A, int AAngle_B, bool Checked) :
        TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, AAngle_A, AAngle_B, AAngle_A, AAngle_B, false)
{
    FName = "����";  // �������������� ��������

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

