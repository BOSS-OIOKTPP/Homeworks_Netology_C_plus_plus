// hw1-NumberOfSides.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
// Задача 1. Фигуры.Количество сторон
// В этом задании вы построите первую простую иерархию классов для заданной предметной области.
//
// Предметная область выглядит следующим образом : есть сущность фигура.Фигуры бывают двух типов : треугольник и четырёхугольник.
// У фигуры есть количество сторон.Для неизвестной фигуры будем считать это количество равным нулю. У треугольника три стороны, у четырёхугольника четыре стороны.
// У любой фигуры мы хотим узнавать количество её сторон, но мы не должны быть способны изменить количество сторон для заданной фигуры извне.
//
// Задача : спроектировать и реализовать классы, описывающие предметную область.
// Продемонстрируйте их работу : создайте по одному экземпляру каждого класса и выведите информацию о количестве его сторон на консоль.
//
// Пример работы программы
// Консоль
// Количество сторон :
// Фигура: 0
// Треугольник : 3
// Четырёхугольник : 4

#include <iostream>
#include <locale>
#include <string>


class TPolygon {
protected:
    int FSides;         // Количество сторон
    std::string FName;  // Названия фигуры
public:
    TPolygon(): FSides(0), FName("Фигура") {}    

    int GetSides() { return FSides; }            
    std::string GetName() { return FName; }
};

// Треугольник
class TTriangle : public TPolygon {
public:
    TTriangle(){
        FSides=3; 
        FName="Треугольник";        
    } 
    int GetSides() { return FSides; }
    std::string GetName() { return FName; }
};

// Четырёхугольник
class TQuadrilateral : public TPolygon {
public:
    TQuadrilateral() {
        FSides = 4;
        FName = "Четырёхугольник";
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
    std::cout << poly.GetName()+": " << poly.GetSides() << std::endl;
    std::cout << tri.GetName() + ": " << tri.GetSides() << std::endl;
    std::cout << quad.GetName() + ": " << quad.GetSides() << std::endl;

    return 0;
}

