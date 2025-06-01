#include <iostream>
#include <locale>

class Fraction
{
private:
    int numerator_;
    int denominator_;

    // Находим наибольший общий делитель
    int gcd(int a, int b) {
        while (b != 0) {
            int t = b;
            b = a % b;
            a = t;
        }
        return a;
    }

    // Сокращение дроби
    void reduce() {
        // Получаем НОД. Числа должны быть положительными
        int d = gcd(abs(numerator_), abs(denominator_)); 
        numerator_ /= d;
        denominator_ /= d;

        // Проверяем, что знаменатель положительный
        if (denominator_ < 0) {
            numerator_ = -numerator_;
            denominator_ = -denominator_;
        }
    }
public:
    // В конструкторе проверяем, чтобы знаменатель не был равен 0
    Fraction(int num, int den) : numerator_(num), denominator_(den) {
        if (den == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен 0");
        }
        // Сокращаем дробь
        reduce();
    }

    // Равно
    // Для сравнения дроби приводим под один общий знаменатель, а потом умножаем неравенство на него для сокращения
    // a / b = c / d  -> 
    // (a * d) / (b * d) = (b * c) / (b * d)   ->           / * (b * d)
    // a * d = b * c
    // 
    // Например, 
    // 1 / 2 = 4 / 8 -> 
    // 1 * 8 = 4 * 2 -> 
    // 8 = 8 -> true
    bool operator==(const Fraction& right) const { return (numerator_ * right.denominator_) == (right.numerator_ * denominator_); }

    // Не равно 
    bool operator!=(const Fraction& right) const { return (numerator_ * right.denominator_) != (right.numerator_ * denominator_); }

    // Меньше
    //    a / b < c / d -> 
    //    a * d < c * b
    // 
    // Например, 
    //    4 / 7 < 3 / 4 -> 
    //    4 * 4 < 3 * 7 -> 
    //    16 < 21 -> true
    bool operator<(const Fraction& right) const { return (numerator_ * right.denominator_) < (right.numerator_ * denominator_); }

    // Больше
    bool operator>(const Fraction& right) const { return (numerator_ * right.denominator_) > (right.numerator_ * denominator_); }

    // Меньше или равно
    bool operator<=(const Fraction& right) const { return ((numerator_ * right.denominator_) < (right.numerator_ * denominator_) ||
                                               (numerator_ * right.denominator_) == (right.numerator_ * denominator_));
    }

    // Больше или равно
    bool operator>=(const Fraction& right) const { return ((numerator_ * right.denominator_) > (right.numerator_ * denominator_) ||
                                               (numerator_ * right.denominator_) == (right.numerator_ * denominator_));
    }

    // Операторы арифметики
    // + сумма
    Fraction operator+(const Fraction& right) const {
        int num = numerator_ * right.denominator_ + right.numerator_ * denominator_;
        int den = denominator_ * right.denominator_;
        return Fraction(num, den);
    }

    // - вычитание
    Fraction operator-(const Fraction& right) const {
        int num = numerator_ * right.denominator_ - right.numerator_ * denominator_;
        int den = denominator_ * right.denominator_;
        return Fraction(num, den);
    }

    // * умножение
    Fraction operator*(const Fraction& right) const {
        int num = numerator_ * right.numerator_;
        int den = denominator_ * right.denominator_;
        return Fraction(num, den);
    }

    // / деление
    Fraction operator/(const Fraction& right) const {
        if (right.numerator_ == 0) {
            throw std::invalid_argument("Нельзя делить на 0");
        }
        int num = numerator_ * right.denominator_;
        int den = denominator_ * right.numerator_;
        return Fraction(num, den);
    }

    // меняем знак числа на противоположный
    Fraction operator-() const { return Fraction(-numerator_, denominator_); }

    // Префиксный инкремент, прибавляем единицу к текущему значению
    // Например,
    // Fraction f(3, 4);
    // Fraction a = ++f;  // f = 7/4, a = 7/4
    // т.е. сначала дробь f = 3/4 превращается в (3 + 4)/4 = 7/4 ,
    // а operator возвращает ссылку на уже изменённый объект f
    Fraction& operator++() {
        numerator_ += denominator_;   // a/b -> (a + b)/b
        reduce();
        return *this;
    }

    // Постфиксный инкремент
    // Например,
    // Fraction f(3, 4);
    // Fraction b = f++;  // b = 7/4 (старое), f = 11/4 (новое)
    // т.е. создали новую переменную и в нее скопировали значение f = 3/4 
    // потом изменили текущую дробь f до 7 / 4 ,
    // а operator возвращает ссылку на копию f со старым значением
    Fraction operator++(int) {
        Fraction t = *this;
        ++(*this);
        return t;
    }

    // Префиксный декремент
    Fraction& operator--() {
        numerator_ -= denominator_;
        reduce();
        return *this;
    }

    // Постфиксный декремент
    Fraction operator--(int) {
        Fraction t = *this;
        --(*this);
        return t;
    }
       
    // Вывод дроби
    friend std::ostream& operator<<(std::ostream& os, const Fraction& f) {
        os << f.numerator_ << "/" << f.denominator_;
        return os;
    }

    // Ввод дроби
    friend std::istream& operator>>(std::istream& is, Fraction& f) {
        is >> f.numerator_ >> f.denominator_;
        if (f.denominator_ == 0) {
            throw std::invalid_argument("Знаменатель не может быть равен нулю");
        }
        f.reduce();
        return is;
    }    
};


int main()
{
    setlocale(LC_ALL, "russian");

    try {
        int num1, den1, num2, den2;

        std::cout << "Введите числитель дроби 1: ";
        std::cin >> num1;
        std::cout << "Введите знаменатель дроби 1: ";
        std::cin >> den1;

        std::cout << "Введите числитель дроби 2: ";
        std::cin >> num2;
        std::cout << "Введите знаменатель дроби 2: ";
        std::cin >> den2;
        std::cout << std::endl;

        Fraction f1(num1, den1);
        Fraction f2(num2, den2);

        std::cout << f1 << " + " << f2 << " = " << (f1 + f2) << std::endl;
        std::cout << f1 << " - " << f2 << " = " << (f1 - f2) << std::endl;
        std::cout << f1 << " * " << f2 << " = " << (f1 * f2) << std::endl;
        std::cout << f1 << " / " << f2 << " = " << (f1 / f2) << std::endl;
        std::cout << std::endl;

        Fraction f3 = f1;  // копия, т.к. ++f1 будет вычислен раньше и испортит результат в консоли
        std::cout << "++" << f3 << " * " << f2 << " = " << (++f1 * f2) << std::endl;
        std::cout << "Значение дроби 1 = " << f1 << std::endl;
        std::cout << std::endl;

        f3 = f1;
        std::cout << f3 << "-- * " << f2 << " = " << (f1-- * f2) << std::endl;
        std::cout << "Значение дроби 1 = " << f1 << std::endl;

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
    }

    //  ТЕСТ
    // 3 / 4 + 4 / 5 = 31 / 20
    // 3 / 4 - 4 / 5 = -1 / 20
    // 3 / 4 * 4 / 5 = 3 / 5
    // 3 / 4 / 4 / 5 = 15 / 16
    // ++3 / 4 * 4 / 5 = 7 / 5
    // Значение дроби 1 = 7 / 4
    // 7 / 4-- * 4 / 5 = 7 / 5
    // Значени дроби 1 = 3 / 4

    return EXIT_SUCCESS;
}

