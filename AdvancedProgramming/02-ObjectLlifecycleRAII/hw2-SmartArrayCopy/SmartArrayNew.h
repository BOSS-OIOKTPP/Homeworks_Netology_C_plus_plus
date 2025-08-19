#pragma once

//#include <iostream>
//#include <stdexcept>
#include <string>

class SmartArray {
private:
    int* FData;             // ��������� �� ������
    int FActualSize;        // ���������� ��������� ��� ������� �������� ������
    int FLogicalSize;       // ����������� ���������� ���������   
public:  
    SmartArray(int size);   // �����������
    ~SmartArray();          // ����������

    int ActualSize() const;         // ���������� ��������� ��� ������� �������� ������
    int LogicalSize() const;        // ����������� ���������� ���������   
    
    void add_element(int value);    // ���������� �������� (� ������������ �����������)

    std::string Print();            // ������ �������

    // ���������� ��������� []
    int& operator[](int index);
    const int& operator[](int index) const;

    // ���������� ��������� =    
    SmartArray& operator=(const SmartArray& other);
};

