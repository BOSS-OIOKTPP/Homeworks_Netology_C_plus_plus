#include "SmartArray.h"

// �����������
SmartArray::SmartArray(int size) {
    FActualSize = size;
    FLogicalSize = 0;
    FData = new int[size];
}
// ����������
SmartArray::~SmartArray() {
    delete[] FData;
}
// ���������� ��������� ��� ������� �������� ������
int SmartArray::ActualSize() { 
    return FActualSize;
}
// ����������� ���������� ���������   
int SmartArray::LogicalSize() {
    return FLogicalSize;
}
// ���������� �������� (� ������������ �����������)
void SmartArray::add_element(int value) {
    // ������� ������ � 2 ���� ������ ��� ��� � �������� � ���� ������ �� ������� �������
    if (FLogicalSize == FActualSize) {
        int* tmpArray = new int[2 * FActualSize];
        for (int i = 0; i < FActualSize; ++i)
            tmpArray[i] = FData[i];
        // ������� ������ ������
        delete[] FData;
        // ���������� ������ �� ����� ������
        FData = tmpArray;
        // ����������� ����������� ������ � 2 ����
        FActualSize *= 2;
    }

    // ����������� ���������� ������ �� 1
    FLogicalSize++;
    // ���������� ��������� ��������
    FData[FLogicalSize-1] = value;    
}

// ���������� ��������� [] ��� ��������
int& SmartArray::operator[](int index) {
    if (index >= FActualSize) {
        throw std::out_of_range("Index out of range");
    }
    return FData[index];
}
const int& SmartArray::operator[](int index) const {
    return operator[](index); // �������� ������������� ������
}