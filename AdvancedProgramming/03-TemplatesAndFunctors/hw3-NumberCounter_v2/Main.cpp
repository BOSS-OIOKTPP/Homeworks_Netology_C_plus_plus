#include <iostream>
#include <string>
#include <windows.h>
#include <vector>



// Функтор для подсчета чисел, делящихся на 3
class DivByThree {
private:
    int sum;
    int count;
public:
    DivByThree(): sum(0), count(0) {}
    void operator()(int value) {
        if (value % 3 == 0) {
            sum += value;
            count++;
        }
    }
    int get_sum() const { return sum; }
    int get_count() const { return count; }
};

// Печать вектора
std::string print_vector(const std::vector<int>& arr) {
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
    std::vector<int> input{ 4, 1, 3, 6, 25, 54 };
    std::cout << "[IN]: " << print_vector(input) << std::endl;

    // Используем функтор для подсчета чисел, делящихся на 3
    DivByThree divByThree;
    for (int i = 0; i < input.size(); ++i)
        divByThree(input[i]);

    std::cout << "[OUT]: get_sum() = " << divByThree.get_sum() << std::endl;
    std::cout << "[OUT]: get_count() = " << divByThree.get_count() << std::endl;

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}