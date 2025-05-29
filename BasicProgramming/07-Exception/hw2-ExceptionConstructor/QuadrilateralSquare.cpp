#include "bad_CreatePolygon.h"
#include "QuadrilateralSquare.h"

// �������
TQuadrilateralSquare::TQuadrilateralSquare(int ALength_a, bool Checked) :
    TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, 90, 90, 90, 90, false)
{
    FName = "�������";  // �������������� ��������

    std::string ErrText;
    if (Checked && !Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

