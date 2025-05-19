// hw1-NumberOfSides.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <locale>

class Parent
{
public:
    Parent(int a)
    {
        std::cout << "Создаю родителя " << a << " \n";
    }
};

class Child : public Parent
{
public:
    Child() : Child(5)
    {
        std::cout << "Создаю потомка\n";
    }
    Child(int a) : Parent(a)
    {
        std::cout << "Создаю потомка " << a << " \n";
    }
};
int main(int argc, char** argv)
{
    setlocale(LC_ALL, "russian");

    Parent parent(3);  // Создаю родителя 3
     Child child_empty; // Создаю родителя 5
                       // Создаю потомка 5
                       // Создаю потомка
    Child child_8(8);  // Создаю родителя 8
                       // Создаю потомка 8
}

