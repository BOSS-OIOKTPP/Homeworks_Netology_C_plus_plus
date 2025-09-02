#include <iostream>
#include <string>
#include <windows.h>
#include <vector>


// Шаблон
template<typename T>
T& square(T& value) {    
    return value *= value; 
}
// Специализация
template<typename T>
std::vector<T>& square(std::vector<T>& arr) {
    for (auto& element : arr) 
        element *= element;
    return arr;
}

template<typename T>
std::string print_vector(const std::vector<T>& arr) {
    std::string str;
    str = "";
    for (int i = 0; i < arr.size(); ++i) {
        str += std::to_string(arr[i]);
        if (i < arr.size() - 1) 
            str += ", ";        
    }
    return str;
}

int main() {
    // Установили кодировку
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Входные данные
    int input1{ 4 };
    std::cout << "[IN]: " << input1 << std::endl;
    std::cout << "[OUT]: " << square(input1) << std::endl;
    std::vector<int> input2{ -1, 4, 8 };
    std::cout << "[IN]: " << print_vector(input2) << std::endl;
    std::cout << "[OUT]: " << print_vector(square(input2)) << std::endl;


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}
