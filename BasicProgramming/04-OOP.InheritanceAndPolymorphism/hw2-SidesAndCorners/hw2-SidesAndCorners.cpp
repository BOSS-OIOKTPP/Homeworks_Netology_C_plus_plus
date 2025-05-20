// hw2-SidesAndCorners.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Задача 2. Фигуры.Стороны и углы
// В этом задании вы усложните иерархию классов для усложнённой предметной области.
//
// У вас появляется информация о длине сторон и углах ваших фигур, а также несколько более конкретных фигур.Теперь в треугольнике вы должны хранить информацию о длине всех его трёх сторон(a, b, c) и значениях его трёх углов(A, B, C).В четырёхугольнике вы храните информацию о длине его четырёх сторон(a, b, c, d) и значениях его четырёх углов(A, B, C, D).
//
// Также у вас появляются более конкретные фигуры :
//
// прямоугольный треугольник(угол C всегда равен 90);
// равнобедренный треугольник(стороны a и c равны, углы A и C равны);
// равносторонний треугольник(все стороны равны, все углы равны 60);
// прямоугольник(стороны a, c и b, d попарно равны, все углы равны 90);
// квадрат(все стороны равны, все углы равны 90);
// параллелограмм(стороны a, c и b, d попарно равны, углы A, C и B, D попарно равны);
// ромб(все стороны равны, углы A, C и B, D попарно равны).
// Вы должны иметь возможность узнать у каждой фигуры длины её сторон и значения её углов, но извне вы не должны быть способны изменить длины сторон и углы.
//
// Не должно быть возможности создать фигуры, не удовлетворяющие перечисленным условиям.Например, нельзя создать квадрат с разными углами.Геометрические соотношения проверять не нужно.Например, сумма углов в треугольнике может быть не равна 180.
//
// Задача: спроектировать и реализовать классы, описывающие предметную область.Продемонстрируйте их работу : создайте по одному экземпляру каждой фигуры и выведите на экран информацию о длинах её сторон и величине её углов.Значения используйте произвольные.
//
// Инициализацию длин сторон и величин углов нужно выполнить с помощью вызова базовых конструкторов.
//
// Для вывода информации о фигуре создайте функцию print_info, которая будет принимать в качестве аргумента указатель на базовый класс фигуры.
//
// Пример работы программы
// Консоль
// Треугольник :
// Стороны: a = 10 b = 20 c = 30
// Углы : A = 50 B = 60 C = 70
//
// Прямоугольный треугольник :
// Стороны: a = 10 b = 20 c = 30
// Углы : A = 50 B = 60 C = 90
//
// Равнобедренный треугольник :
// Стороны: a = 10 b = 20 c = 10
// Углы : A = 50 B = 60 C = 50
//
// Равносторонний треугольник :
// Стороны: a = 30 b = 30 c = 30
// Углы : A = 60 B = 60 C = 60
//
// Четырёхугольник :
// Стороны : a = 10 b = 20 c = 30 d = 40
// Углы : A = 50 B = 60 C = 70 D = 80
//
// Прямоугольник :
// Стороны : a = 10 b = 20 c = 10 d = 20
// Углы : A = 90 B = 90 C = 90 D = 90
//
// Квадрат :
// Стороны : a = 20 b = 20 c = 20 d = 20
// Углы : A = 90 B = 90 C = 90 D = 90
//
// Параллелограмм :
// Стороны : a = 20 b = 30 c = 20 d = 30
// Углы : A = 30 B = 40 C = 30 D = 40
//
// Ромб :
// Стороны : a = 30 b = 30 c = 30 d = 30
// Углы : A = 30 B = 40 C = 30 D = 40


#include <iostream>
#include <locale>
#include <string>


class TPolygon {
protected:
    int FSides;         // Количество сторон
    std::string FName;  // Названия фигуры
public:
    TPolygon() : FSides(0), FName("Фигура") {}

    int GetSides() { return FSides; }
    std::string GetName() { return FName; }

    void SetSides(int ASides) { FSides = ASides; }
    void SetName(std::string AName) { FName = AName; }
};

// Треугольник
class TTriangle : public TPolygon {
private:
    int FSideLength_a;
    int FSideLength_b;
    int FSideLength_c;
    int FSideAngle_A;
    int FSideAngle_B;
    int FSideAngle_C;
public:
    TTriangle() {
        SetSides(3);
        SetName("Треугольник");

    }
    int GetSides() { return FSides; }
    std::string GetName() { return FName; }
    int GetSideLength_a() { return FSideLength_a; }
    int GetSideLength_b() { return FSideLength_b; }
    int GetSideLength_c() { return FSideLength_c; }
    int GetSideAngle_A() { return FSideAngle_A; }
    int GetSideAngle_B() { return FSideAngle_B; }
    int GetSideAngle_C() { return FSideAngle_C; }



};

Пример!!!

//#include <iostream>
//#include <string>
//
//class TPolygon {
//protected:
//    int FSides;
//    std::string FName;
//public:
//    TPolygon() : FSides(0), FName("Фигура") {}
//    void PrintInfo() const {
//        std::cout << FName << " (сторон: " << FSides << ")\n";
//    }
//};
//
//class TTriangle : public TPolygon {
//    double FBase, FHeight;
//public:
//    TTriangle(double base, double height) : FBase(base), FHeight(height) {
//        FSides = 3;
//        FName = "Треугольник";
//    }
//};
//
//int main() {
//    TTriangle tri(5.0, 4.0);
//    tri.PrintInfo();  // Вывод: "Треугольник (сторон: 3)"
//    return 0;
//}





// Четырёхугольник
class TQuadrilateral : public TPolygon {
public:
    TQuadrilateral() {
        SetSides(4);
        SetName("Четырёхугольник");
    }
    int GetSides() { return FSides; }
    std::string GetName() { return FName; }
};


int main()
{
    setlocale(LC_ALL, "russian");

    TPolygon poly;
    TTriangle tri;
    TQuadrilateral quad;

    std::cout << "Количество сторон:" << std::endl;
    std::cout << poly.GetName() + ": " << poly.GetSides() << std::endl;
    std::cout << tri.GetName() + ": " << tri.GetSides() << std::endl;
    std::cout << quad.GetName() + ": " << quad.GetSides() << std::endl;

    return 0;
}

