#include <iostream>
#include "bad_CreatePolygon.h"
#include "Triangle.h"

// �����������
TTriangle::TTriangle(int ALength_a, int ALength_b, int ALength_c,
        int AAngle_A, int AAngle_B, int AAngle_C) {
    FSides = 3;
    FName = "�����������";
    FLength_a = ALength_a;
    FLength_b = ALength_b;
    FLength_c = ALength_c;
    FAngle_A = AAngle_A;
    FAngle_B = AAngle_B;
    FAngle_C = AAngle_C;

    std::string ErrText;
    if (!Check(ErrText)) { throw bad_CreatePolygon(ErrText); }
}

int TTriangle::GetLength_a() { return FLength_a; }
int TTriangle::GetLength_b() { return FLength_b; }
int TTriangle::GetLength_c() { return FLength_c; }
int TTriangle::GetAngle_A() { return FAngle_A; }
int TTriangle::GetAngle_B() { return FAngle_B; }
int TTriangle::GetAngle_C() { return FAngle_C; }

// �������� - ����� ����� ������ ���� ����� 180    
bool TTriangle::Check(std::string& Err) { 
    bool res{ FAngle_A + FAngle_B + FAngle_C == 180 };
    Err = "";
    if (!res) { Err = GetName() + ". ������ �������� ������. �������: ����� ����� �� ����� 180."; }
    return res; }

// ������
void TTriangle::Print() {
    std::cout << GetName() + " ( " << "c������ :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << "; "
         << "���� :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " ) ������" << std::endl;    
}


