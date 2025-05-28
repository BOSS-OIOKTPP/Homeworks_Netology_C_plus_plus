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

    // �������� 
    virtual bool Check(std::string& Err);
    // ������
    virtual void Print();
};

