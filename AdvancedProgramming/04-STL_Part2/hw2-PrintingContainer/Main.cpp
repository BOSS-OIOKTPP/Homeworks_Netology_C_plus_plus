#include <iostream>
#include <Windows.h>
#include <set>
#include <vector>
#include <list>


template<typename T>
void print_container( T& container ) {
    bool first = true;
    for ( auto& element : container ) {
        if (!first) { std::cout << ", "; }
        std::cout << element;
        first = false;
    }
    std::cout << std::endl;
}

int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    std::set<std::string> test_set = { "one", "two", "three", "four" };
    print_container(test_set); // four one three two

    std::list<std::string> test_list = { "one", "two", "three", "four" };
    print_container(test_list); // one, two, three, four

    std::vector<std::string> test_vector = { "one", "two", "three", "four" };
    print_container(test_vector); // one, two, three, four


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
