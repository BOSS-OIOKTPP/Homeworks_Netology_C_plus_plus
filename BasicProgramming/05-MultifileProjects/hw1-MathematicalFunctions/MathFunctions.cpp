#include "MathFunctions.h"

// ��������
int Add(int A, int B) {	return A + B;}
// ���������
int Subtract(int A, int B) { return A - B; }
// ���������
int Multiply(int A, int B) { return A * B; }
// �������
int Divide(int A, int B) { return A / B; }
// ���������� � �������. B>0
int Power(int A, int B) {
    int result = 1;
    for (int i = 0; i < B; ++i) result *= A;
    return result;    
}