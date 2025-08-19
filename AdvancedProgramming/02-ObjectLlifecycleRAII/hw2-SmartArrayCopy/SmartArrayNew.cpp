#include <iostream>
#include <string>
#include "SmartArrayNew.h"

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
int SmartArray::ActualSize() const { 
    return FActualSize;
}
// ����������� ���������� ���������   
int SmartArray::LogicalSize() const {
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

// ������ �������
std::string SmartArray::Print() {
    std::string str;
    str = "";
    for (int i = 0; i < FLogicalSize; ++i)              
        str += std::to_string(FData[i]) + " ";
    for (int i = FLogicalSize; i < FActualSize; ++i)
        str += "_ ";
    return str;
}

// ���������� ��������� [] 
int& SmartArray::operator[](int index) {
    if (index >= FLogicalSize) {
        //throw std::out_of_range("Index out of range");
        throw std::out_of_range(
            "������ ������� SmartArray[" + std::to_string(index) + "]"
            " ������� �� ������� (����������� ������ [0; " + std::to_string(FLogicalSize-1) + "])"
        );
    }
    return FData[index];
}
const int& SmartArray::operator[](int index) const {
    return operator[](index); // �������� ������������� ������
}

// ���������� ��������� =
SmartArray& SmartArray::operator=(const SmartArray& other) {
    if (this != &other) { // �������� �� ����������������
        if (FLogicalSize < other.FLogicalSize) {
            // ���������� ���������� ���������
            for (int i = 0; i < (other.FLogicalSize - FLogicalSize); ++i) 
                this->add_element(0);
        }

        // ��������� ����������� �� ������ ������� � ������
        for (int i = 0; i < other.FLogicalSize; ++i)
            FData[i] = other.FData[i];
    }
    return *this;
}