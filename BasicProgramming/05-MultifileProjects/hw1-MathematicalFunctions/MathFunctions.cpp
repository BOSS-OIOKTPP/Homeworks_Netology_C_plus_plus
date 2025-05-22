#include "MathFunctions.h"

// сложение
int Add(int A, int B) {	return A + B;}
// вычитание
int Subtract(int A, int B) { return A - B; }
// умножение
int Multiply(int A, int B) { return A * B; }
// деление
int Divide(int A, int B) { return A / B; }
// возведение в степень. B>0
int Power(int A, int B) {
    int result = 1;
    for (int i = 0; i < B; ++i) result *= A;
    return result;    
}