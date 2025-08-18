#pragma once

#include <iostream>
#include <stdexcept>

class SmartArray {
private:
    int* FData;             // ��������� �� ������
    int FActualSize;        // ���������� ��������� ��� ������� �������� ������
    int FLogicalSize;       // ����������� ���������� ���������   
public:  
    SmartArray(int size);   // �����������
    ~SmartArray();          // ����������

    int ActualSize();       // ���������� ��������� ��� ������� �������� ������
    int LogicalSize();      // ����������� ���������� ���������   
    
    void add_element(int value); // ���������� �������� (� ������������ �����������)

    // ���������� ��������� [] ��� ��������
    int& operator[](int index);
    const int& operator[](int index) const;
};

