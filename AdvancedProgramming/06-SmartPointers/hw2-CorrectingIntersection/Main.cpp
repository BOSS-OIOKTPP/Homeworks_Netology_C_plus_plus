#include <iostream>
#include <Windows.h>
//#include <vector>
//#include <memory>

class node
{
public:
    int m_value;

    // Было
    //std::shared_ptr<node> parent;
     
    // Стало
    std::weak_ptr<node> parent;  // Не увеличивает счетчик ссылок на объект и не владеет им

    node(int value) : m_value{ value } {};
    ~node() { std::cout << "destructor called\n"; }
};

int main()
{
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    {
        auto node1 = std::make_shared<node>(1);
        auto node2 = std::make_shared<node>(2);
        node1->parent = node2;
        node2->parent = node1;
    }

    //std::cout << std::endl;
    //system("pause");

    return EXIT_SUCCESS;
}