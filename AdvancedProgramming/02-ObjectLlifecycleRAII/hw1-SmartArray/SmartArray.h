#pragma once

#include <iostream>
#include <stdexcept>

class SmartArray {
private:
    int* FData;             // ��������� �� ������
    int FActualSize;        // ���������� ��������� ��� ������� �������� ������
    int FLogicalSize;       // ����������� ���������� ���������   

    int at(int index);      // �������� ������� �� ������� � ���������
public:  
    SmartArray(int size);   // �����������
    ~SmartArray();          // ����������

    int ActualSize();       // ���������� ��������� ��� ������� �������� ������
    int LogicalSize();      // ����������� ���������� ���������   
    
    void add_element(int value); // ���������� �������� (� ������������ �����������)

    // ���������� ��������� [] ��� ��������
    int& operator[](size_t index) {
        return const_cast<int&>(static_cast<const SmartArray&>(*this).at(index));
    }
};

// ������ �������������
int main() {
    
    
    
    //SmartArray arr(3); // ������� ������ �� 3 ��������

    //// ��������� �������� (������ ��� ����������)
    //for (int i = 0; i < 10; ++i) {
    //    arr.push_back(i * 10);
    //}

    //// �������� ��������
    //for (size_t i = 0; i < arr.size(); ++i) {
    //    std::cout << arr[i] << " "; // ���������� operator[]
    //}

    //// �������� ��������� ������
    //try {
    //    std::cout << "\nElement at 100: " << arr.at(100);
    //}
    //catch (const std::out_of_range& e) {
    //    std::cerr << "\nError: " << e.what();
    //}
    

    system("pause");

    return EXIT_SUCCESS;
}
