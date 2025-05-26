// hw3-Methods.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Задача 3. Фигуры. Методы
// В этом задании вы добавите в вашу иерархию классов больше функциональности.
//
// Теперь ваши фигуры должны уметь немного больше :
//
// 1) выводить информацию о себе;
// 2) проверять правильность своих данных.
// 
// Ваши фигуры :
//
// фигура(количество сторон равно 0);
// треугольник(стороны и углы произвольные, количество сторон равно 3, сумма углов равна 180);
// прямоугольный треугольник(угол C всегда равен 90);
// равнобедренный треугольник(стороны a и c равны, углы A и C равны);
// равносторонний треугольник(все стороны равны, все углы равны 60);
// четырёхугольник(стороны и углы произвольные, количество сторон равно 4, сумма углов равна 360);
// прямоугольник(стороны a, c и b, d попарно равны, все углы равны 90);
// квадрат(все стороны равны, все углы равны 90);
// параллелограмм(стороны a, c и b, d попарно равны, углы A, C и B, D попарно равны);
// ромб(все стороны равны, углы A, C и B, D попарно равны).
// 
// Вы должны иметь возможность попросить фигуру вывести информацию о себе на консоль, а также узнать, является ли фигура правильной, 
// то есть выполняются ли условия, указанные в списке выше.
//
// 1) Информация о фигуре включает в себя :
//
//      название фигуры;
//      количество сторон;
//      длины её сторон, если есть;
//      величины её углов, если есть;
//      является ли фигура правильной.
// 
// Задача: спроектировать и реализовать классы, описывающие предметную область.
// Продемонструйте их работу: создайте по одному экземпляру каждой фигуры и выведите на экран информацию о фигурах.
//
// Реализуйте методы вывода на консоль и проверки правильности фигуры с помощью виртуальных функций и переопределений. Используйте вызов базовой версии метода.
//
// Ваша задача — работать с экземплярами дочерних классов полиморфно, то есть с помощью указателя на базовый класс.
//
// Пример работы программы
// Консоль
// 
// Фигура :
// Правильная
// Количество сторон : 0
//
// Треугольник :
// Правильная
// Количество сторон : 3
// Стороны : a = 10 b = 20 c = 30
// Углы : A = 50 B = 60 C = 70
//
// Прямоугольный треугольник :
// Неправильная
// Количество сторон : 3
// Стороны : a = 10 b = 20 c = 30
// Углы : A = 50 B = 60 C = 90
//
// Прямоугольный треугольник :
// Правильная
// Количество сторон : 3
// Стороны : a = 10 b = 20 c = 30
// Углы : A = 50 B = 40 C = 90
//
// Равнобедренный треугольник :
// Неправильная
// Количество сторон : 3
// Стороны : a = 10 b = 20 c = 10
// Углы : A = 50 B = 60 C = 50
//
// Равносторонний треугольник :
// Правильная
// Количество сторон : 3
// Стороны : a = 30 b = 30 c = 30
// Углы : A = 60 B = 60 C = 60
//
// Четырёхугольник :
// Неправильная
// Количество сторон : 4
// Стороны : a = 10 b = 20 c = 30 d = 40
// Углы : A = 50 B = 60 C = 70 D = 80
//
// Прямоугольник :
// Правильная
// Количество сторон : 4
// Стороны : a = 10 b = 20 c = 10 d = 20
// Углы : A = 90 B = 90 C = 90 D = 90
//
// Квадрат :
// Правильная
// Количество сторон : 4
// Стороны : a = 20 b = 20 c = 20 d = 20
// Углы : A = 90 B = 90 C = 90 D = 90
//
// Параллелограмм :
// Неправильная
// Количество сторон : 4
// Стороны : a = 20 b = 30 c = 20 d = 30
// Углы : A = 30 B = 40 C = 30 D = 40
//
// Ромб :
// Неправильная
// Количество сторон : 4
// Стороны : a = 30 b = 30 c = 30 d = 30
// Углы : A = 30 B = 40 C = 30 D = 40


#include <iostream>
#include <locale>
#include <string>

const std::string varStateStrTrue{ "Правильная"};
const std::string varStateStrFalse{ "Неправильная" };

class TPolygon {
protected:
    int FSides;         // Количество сторон
    std::string FName;  // Названия фигуры
public:
    TPolygon() : FSides(0), FName("Фигура") {}

    int GetSides() { return FSides; }
    std::string GetName() { return FName; }

    // Проверка 
    virtual bool Check() { return true; }

    // Печать
    virtual void Print() {
        std::cout << GetName() + " :" << std::endl;
        std::cout << (Check()==true ? varStateStrTrue : varStateStrFalse) << std::endl;
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
        FSides = 3;
        FName = "Треугольник";
        FLength_a = ALength_a;
        FLength_b = ALength_b;
        FLength_c = ALength_c;
        FAngle_A = AAngle_A;
        FAngle_B = AAngle_B;
        FAngle_C = AAngle_C;
    }

    int GetLength_a() { return FLength_a; }
    int GetLength_b() { return FLength_b; }
    int GetLength_c() { return FLength_c; }
    int GetAngle_A() { return FAngle_A; }
    int GetAngle_B() { return FAngle_B; }
    int GetAngle_C() { return FAngle_C; }

    // Проверку проводим по сумме углов 
    virtual bool Check() { return (FAngle_A + FAngle_B + FAngle_C == 180); }
     
    // Печать
    virtual void Print() {
        std::cout << GetName() + " :" << std::endl;
        std::cout << (Check() == true ? varStateStrTrue : varStateStrFalse) << std::endl;
        std::cout << "Количество сторон : " << GetSides() << std::endl;
        std::cout << "Стороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << std::endl;
        std::cout << "Углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << std::endl;
        std::cout << std::endl;
    }
};

// Прямоугольный треугольник - угол C всегда равен 90;
class TTriangleRight : public TTriangle {
public:
    TTriangleRight(int ALength_a, int ALength_b, int ALength_c, int AAngle_A, int AAngle_B) :
        TTriangle(ALength_a, ALength_b, ALength_c, AAngle_A, AAngle_B, 90)
    {
        FName = "Прямоугольный треугольник";  // Переопределяем название
    }
};

// Равнобедренный треугольник - стороны a и c равны, углы A и C равны;
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
        FSides = 4;
        FName = "Четырёхугольник";
        FLength_a = ALength_a;
        FLength_b = ALength_b;
        FLength_c = ALength_c;
        FLength_d = ALength_d;
        FAngle_A = AAngle_A;
        FAngle_B = AAngle_B;
        FAngle_C = AAngle_C;
        FAngle_D = AAngle_D;
    }

    int GetLength_a() { return FLength_a; }
    int GetLength_b() { return FLength_b; }
    int GetLength_c() { return FLength_c; }
    int GetLength_d() { return FLength_d; }
    int GetAngle_A() { return FAngle_A; }
    int GetAngle_B() { return FAngle_B; }
    int GetAngle_C() { return FAngle_C; }
    int GetAngle_D() { return FAngle_D; }

    // Проверку проводим по сумме углов 
    virtual bool Check() { return (FAngle_A + FAngle_B + FAngle_C + FAngle_D == 360); }

    // Печать
    virtual void Print() {
        std::cout << GetName() + " :" << std::endl;
        std::cout << (Check() == true ? varStateStrTrue : varStateStrFalse) << std::endl;
        std::cout << "Количество сторон : " << GetSides() << std::endl;
        std::cout << "Стороны :" << " a = " << GetLength_a() << " b = " << GetLength_b() << " c = " << GetLength_c() << " d = " << GetLength_d() << std::endl;
        std::cout << "Углы :" << " A = " << GetAngle_A() << " B = " << GetAngle_B() << " C = " << GetAngle_C() << " D = " << GetAngle_D() << std::endl;
        std::cout << std::endl;
    }
};

// Прямоугольник
class TQuadrilateralRect : public TQuadrilateral {
public:
    TQuadrilateralRect(int ALength_a, int ALength_b) :
        TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, 90, 90, 90, 90)
    {
        FName = "Прямоугольник";  // Переопределяем название
    }
};

// Квадрат
class TQuadrilateralSquare : public TQuadrilateral {
public:
    TQuadrilateralSquare(int ALength_a) :
        TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, 90, 90, 90, 90)
    {
        FName = "Квадрат";  // Переопределяем название
    }
};

// Параллелограмм
class TQuadrilateralParallelogram : public TQuadrilateral {
public:
    TQuadrilateralParallelogram(int ALength_a, int ALength_b, int AAngle_A, int AAngle_B) :
        TQuadrilateral(ALength_a, ALength_b, ALength_a, ALength_b, AAngle_A, AAngle_B, AAngle_A, AAngle_B)
    {
        FName = "Параллелограмм";  // Переопределяем название
    }
};

// Ромб
class TQuadrilateralRhomb : public TQuadrilateral {
public:
    TQuadrilateralRhomb(int ALength_a, int AAngle_A, int AAngle_B) :
        TQuadrilateral(ALength_a, ALength_a, ALength_a, ALength_a, AAngle_A, AAngle_B, AAngle_A, AAngle_B)
    {
        FName = "Ромб";  // Переопределяем название
    }
};


// Печать
void Print_Info(TPolygon& P) {
    P.Print();
}


// Главная программа
int main()
{
    setlocale(LC_ALL, "russian");

    // Фигура:
    // Правильная
    // Количество сторон : 0
    TPolygon t0;

    // Треугольник :
    // Правильная
    // Количество сторон : 3
    // Стороны : a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 70
    TTriangle t1(10, 20, 30, 50, 60, 70);

    // Прямоугольный треугольник :
    // Неправильная
    // Количество сторон : 3
    // Стороны : a = 10 b = 20 c = 30
    // Углы : A = 50 B = 60 C = 90
    TTriangleRight t2_1(10, 20, 30, 50, 60);

    // Прямоугольный треугольник :
    // Неправильная
    // Количество сторон : 3
    // Стороны : a = 10 b = 20 c = 30
    // Углы : A = 50 B = 40 C = 90
    TTriangleRight t2_2(10, 20, 30, 50, 40);

    // Равнобедренный треугольник :
    // Неправильная
    // Количество сторон : 3
    // Стороны : a = 10 b = 20 c = 10
    // Углы : A = 50 B = 60 C = 50
    TTriangleIsosceles t3(10, 20, 50, 60);

    // Равносторонний треугольник :
    // Правильная
    // Количество сторон : 3
    // Стороны : a = 30 b = 30 c = 30
    // Углы : A = 60 B = 60 C = 60
    TTriangleEquilateral t4(30);
    
    // Четырёхугольник :
    // Неправильная
    // Количество сторон : 4
    // Стороны : a = 10 b = 20 c = 30 d = 40
    // Углы : A = 50 B = 60 C = 70 D = 80
    TQuadrilateral t5(10, 20, 30, 40, 50, 60, 70, 80);

    // Прямоугольник :
    // Правильная
    // Количество сторон : 4
    // Стороны : a = 10 b = 20 c = 10 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    TQuadrilateralRect t6(10, 20);

    // Квадрат :
    // Правильная
    // Количество сторон : 4
    // Стороны : a = 20 b = 20 c = 20 d = 20
    // Углы : A = 90 B = 90 C = 90 D = 90
    TQuadrilateralSquare t7(20);

    // Параллелограмм :
    // Неправильная
    // Количество сторон : 4
    // Стороны : a = 20 b = 30 c = 20 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    TQuadrilateralParallelogram t8(20, 30, 30, 40);

    // Ромб :
    // Неправильная
    // Количество сторон : 4
    // Стороны : a = 30 b = 30 c = 30 d = 30
    // Углы : A = 30 B = 40 C = 30 D = 40
    TQuadrilateralRhomb t9(30, 30, 40);


    // Вывод информации
    Print_Info(t0);
    Print_Info(t1);
    Print_Info(t2_1);
    Print_Info(t2_2);
    Print_Info(t3);
    Print_Info(t4);
    Print_Info(t5);
    Print_Info(t6);
    Print_Info(t7);
    Print_Info(t8);
    Print_Info(t9);


    return 0;
}
