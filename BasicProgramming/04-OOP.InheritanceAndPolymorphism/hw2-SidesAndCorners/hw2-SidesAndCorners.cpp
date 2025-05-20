// hw2-SidesAndCorners.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Задача 2. Фигуры.Стороны и углы
// В этом задании вы усложните иерархию классов для усложнённой предметной области.
//
// У вас появляется информация о длине сторон и углах ваших фигур, а также несколько более конкретных фигур.
// Теперь в треугольнике вы должны хранить информацию о длине всех его трёх сторон(a, b, c) и значениях его трёх углов(A, B, C).
// В четырёхугольнике вы храните информацию о длине его четырёх сторон(a, b, c, d) и значениях его четырёх углов(A, B, C, D).
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
// 
// ОГРАНИЧЕНИЯ
// 
// 1) Вы должны иметь возможность узнать у каждой фигуры длины её сторон и значения её углов, но извне вы не должны быть способны изменить длины сторон и углы.
//
// 2) Не должно быть возможности создать фигуры, не удовлетворяющие перечисленным условиям.Например, нельзя создать квадрат с разными углами.
// Геометрические соотношения проверять не нужно.Например, сумма углов в треугольнике может быть не равна 180.
//
// Задача: спроектировать и реализовать классы, описывающие предметную область.
// Продемонстрируйте их работу : создайте по одному экземпляру каждой фигуры и выведите на экран информацию о длинах её сторон и величине её углов.
// Значения используйте произвольные.
//
// 3) Инициализацию длин сторон и величин углов нужно выполнить с помощью вызова базовых конструкторов.
//
// 4) Для вывода информации о фигуре создайте функцию print_info, которая будет принимать в качестве аргумента указатель на базовый класс фигуры.
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

    virtual void Print() {
        std::cout << GetName() + " :" << std::endl;
        std::cout << "Количество сторон : " << GetSides() << std::endl;
        std::cout << std::endl;
    }
};

// Треугольник
class TTriangle : public TPolygon {
protected:
    int FLength_a;
    int FLength_b;
    int FLength_c;
    int FAngle_A;
    int FAngle_B;
    int FAngle_C;
public:
    TTriangle(int ALength_a, int ALength_b, int ALength_c,
              int AAngle_A, int AAngle_B, int AAngle_C) {
        FSides    = 3;
        FName     = "Треугольник";        
        FLength_a = ALength_a;
        FLength_b = ALength_b;
        FLength_c = ALength_c;
        FAngle_A  = AAngle_A;
        FAngle_B  = AAngle_B;
        FAngle_C  = AAngle_C;
    }
    
    int GetLength_a() { return FLength_a; }
    int GetLength_b() { return FLength_b; }
    int GetLength_c() { return FLength_c; }
    int GetAngle_A() { return FAngle_A; }
    int GetAngle_B() { return FAngle_B; }
    int GetAngle_C() { return FAngle_C; }

    void Print() override {
        std::cout << GetName() + " :" << std::endl;
        std::cout << "Стороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << std::endl;
        std::cout << "Углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << std::endl;
        std::cout << std::endl;
    }
};

// Прямоугольный треугольник - угол C всегда равен 90);
class TTriangleRight : public TTriangle {
public:
    TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B) :
        TTriangle(ALength_a, ALength_b, ALength_c, AAngle_A, AAngle_B, 90) 
    {
        FName = "Прямоугольный треугольник";  // Переопределяем название
    }
};

// Равнобедренный треугольник - стороны a и c равны, углы A и C равны);
class TTriangleIsosceles : public TTriangle {
public:
    TTriangleIsosceles(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) :
        TTriangle(ALength_a, ALength_b, ALength_a, AAngle_A, AAngle_B, AAngle_A)
    {
        FName = "Равнобедренный треугольник";  // Переопределяем название
    }
};

// Равносторонний треугольник - все стороны равны, все углы равны 60;
class TTriangleEquilateral : public TTriangleIsosceles {
public:
    TTriangleEquilateral(int ALength_a) :
        TTriangleIsosceles(ALength_a, ALength_a, 60, 60)
    {
        FName = "Равносторонний треугольник";  // Переопределяем название
    }    
};


// Четырёхугольник
class TQuadrilateral : public TPolygon {
private:
    int FLength_a;
    int FLength_b;
    int FLength_c;
    int FLength_d;
    int FAngle_A;
    int FAngle_B;
    int FAngle_C;
    int FAngle_D;
public:
    TQuadrilateral(int ALength_a, int ALength_b, int ALength_c, int ALength_d,
        int AAngle_A, int AAngle_B, int AAngle_C, int AAngle_D) {
        FSides    = 4;
        FName     = "Четырёхугольник";
        FLength_a = ALength_a;
        FLength_b = ALength_b;
        FLength_c = ALength_c;
        FAngle_A  = AAngle_A;
        FAngle_B  = AAngle_B;
        FAngle_C  = AAngle_C;
    }
    //int GetSides() { return FSides; }
    //std::string GetName() { return FName; }
    int GetLength_a() { return FLength_a; }
    int GetLength_b() { return FLength_b; }
    int GetLength_c() { return FLength_c; }
    int GetLength_d() { return FLength_d; }
    int GetAngle_A() { return FAngle_A; }
    int GetAngle_B() { return FAngle_B; }
    int GetAngle_C() { return FAngle_C; }
    int GetAngle_D() { return FAngle_D; }

    void Print() override {
        std::cout << GetName() + " :" << std::endl;
        std::cout << "Стороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << " d = " << GetLength_d() << std::endl;
        std::cout << "Углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " D = " << GetAngle_D() << std::endl;
        std::cout << std::endl;
    }
};

// Печать
void Print_Info(TPolygon& P) {
    P.Print();
}

int main()
{
    setlocale(LC_ALL, "russian");

    // Треугольник:
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 70
    TTriangle t1(10, 20, 30, 50, 60, 70);

    // Прямоугольный треугольник :
    // Стороны: a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 90
    TTriangleRight t2(10, 20, 30, 50, 60);

    // Равнобедренный треугольник :
    // Стороны: a = 10 b = 20 c = 10
    // Углы : A = 50 B = 60 C = 50
    TTriangleIsosceles t3(10, 20, 50, 60);
    
    // Равносторонний треугольник :
    // Стороны: a = 30 b = 30 c = 30
    // Углы : A = 60 B = 60 C = 60
    TTriangleEquilateral t4(30);

    
    Print_Info(t1);
    Print_Info(t2);
    Print_Info(t3);
    Print_Info(t4);


    return 0;
}
