#pragma once
#include <string>

// ������� �����
class TPolygon {
protected:
    int FSides;         // ���������� ������
    std::string FName;  // �������� ������
public:
    TPolygon();

    int GetSides();
    std::string GetName();

    virtual void Print();
};

