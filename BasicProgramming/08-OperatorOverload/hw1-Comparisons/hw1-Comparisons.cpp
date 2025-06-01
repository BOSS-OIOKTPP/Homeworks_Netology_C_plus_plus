#include <iostream>
#include <windows.h>
#include <string>

class Fraction
{
private:
    int numerator_;
    int denominator_;

public:
    Fraction(int numerator, int denominator)
    {
        numerator_ = numerator;
        denominator_ = denominator;
    }

    // Для сравнения дроби приводим под один общий знаменатель, а потом умножаем неравенство на него для сокращения
    // a / b = c / d  -> 
    // a * d / b * d = b * c / b * d   ->           / * bd
    // a * d = b * c
    // 
    // Например, 
    // 1 / 2 = 4 / 8 -> 
    // 1 * 8 = 4 * 2 -> 
    // 8 = 8 -> true
    bool operator==(Fraction& right) { return (numerator_ * right.denominator_) == (right.numerator_ * denominator_); }

    // Просто инвертирует результат 
    bool operator!=(Fraction& right) { return (numerator_ * right.denominator_) != (right.numerator_ * denominator_); }

    //    a / b < c / d -> 
    //    a * d < c * b
    // 
    // Например, 
    //    4 / 7 < 3 / 4 -> 
    //    4 * 4 < 3 * 7 -> 
    //    16 < 21 -> true
    bool operator<(Fraction& right) { return (numerator_ * right.denominator_) < (right.numerator_ * denominator_); }

    // обратный результат
    bool operator>(Fraction& right) { return (numerator_ * right.denominator_) > (right.numerator_ * denominator_); }
    
    // комбинируем условия
    bool operator<=(Fraction& right) { return ( (numerator_ * right.denominator_) < (right.numerator_ * denominator_) ||
                                                (numerator_ * right.denominator_) == (right.numerator_ * denominator_) ); }
    
    // комбинируем условия
    bool operator>=(Fraction& right) { return ( (numerator_ * right.denominator_) > (right.numerator_ * denominator_) ||
                                                (numerator_ * right.denominator_) == (right.numerator_ * denominator_)); }        
};


int main()
{
    // Устанавливаем кодировку консоли в UTF-8
    SetConsoleOutputCP(CP_UTF8);
    SetConsoleCP(CP_UTF8);

    Fraction f1(4, 3);
    Fraction f2(6, 11);

    std::cout << "f1" << ((f1 == f2) ? " == " : " not == ") << "f2" << '\n';
    std::cout << "f1" << ((f1 != f2) ? " != " : " not != ") << "f2" << '\n';
    std::cout << "f1" << ((f1 < f2) ? " < " : " not < ") << "f2" << '\n';
    std::cout << "f1" << ((f1 > f2) ? " > " : " not > ") << "f2" << '\n';
    std::cout << "f1" << ((f1 <= f2) ? " <= " : " not <= ") << "f2" << '\n';
    std::cout << "f1" << ((f1 >= f2) ? " >= " : " not >= ") << "f2" << '\n';

    return EXIT_SUCCESS;

}

