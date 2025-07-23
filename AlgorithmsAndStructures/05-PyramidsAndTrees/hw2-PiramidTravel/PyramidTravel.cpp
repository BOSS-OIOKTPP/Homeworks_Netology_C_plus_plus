#include <iostream>
#include <string>
#include <windows.h>

// Вычислим уровень дерева
// Для этого поднимаемся от текущего узла к корню
// Каждая итерация (index - 1) / 2 даёт индекс родителя,
// а каждый подъём к родителю увеличивает уровень на 1
int calculate_level(int index) {
    int level = 0;
    while (index > 0) {
        index = (index - 1) / 2;
        level++;
    }
    return level;
}

void print_pyramid(int* arr, int size, int select) {
    
    if (size==0) {
        std::cout << "Пирамида пуста" << std::endl;
        return;
    }

    // Корневой элемент
    int level = 0;
    std::string child_type = "root";
    std::string child_select = ((select == 0) ? "     *" : "");
    std::cout << level << " "<< child_type << " " << arr[0] << child_select << std::endl;

    for (int i = 1; i < size; ++i) {
        level = calculate_level(i);
        int parent_index = (i - 1) / 2;
        int parent_value = arr[parent_index];
        child_type = (i % 2 == 1) ? "left" : "right";
        child_select = ((select == i) ? "     *" : "");

        std::cout << level << " " << child_type << "(" << parent_value << ") " << arr[i] << child_select << std::endl;
    }
};

// Печатаем массив
void print_array(int* arr, int size) {
    std::cout << "[";
    for (int i = 0; i < size; i++) {
        std::cout << arr[i] << (i==(size-1)?"":", ");
    }
    std::cout << "]";
}

// ***   Движение по пирамиде   ***
int travel(int* arr, int size) {
    char inputChar;
    int index{0};           // Текущий индекс, где мы находимся. По умолчанию - это вершина 
    std::string strErr1;    // Сообщение об ошибке

    while (true) {
        // Очищаем консоль 
        system("cls");

        std::cout << "Для движения по пирамиде используйте клавиши:" << std::endl;
        std::cout << "W - вверх, A - влево, D - вправо + Enter" << std::endl;
        std::cout << "Для выхода нажмите Q + Enter" << std::endl;
        std::cout << std::endl;

        // Выводим массив
        std::cout << "Пирамида: " << std::endl;
        print_pyramid(arr, size, index);
        std::cout << std::endl;

        // Показываем ошибку
        if (strErr1 != "")
            std::cout << strErr1 << std::endl << std::endl;

        std::cout << "Выберите направление: ";
        std::cin >> inputChar;
        std::cin.clear(); // Сбрасываем флаги ошибок
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        // Вычисляем текущее положение
        switch (inputChar) {
        case 'w':
        case 'W':
            // вверх
            if (index == 0)
                strErr1 = "Ошибка! Отсутствует родитель";
            else {
                index = (index - 1) / 2;
                strErr1 = "";
            }                
            break;
        case 'a':            
        case 'A':
            // влево
            if (2*index+1 > (size-1))
                strErr1 = "Ошибка! Отсутствует левый потомок";
            else {
                index = 2 * index + 1;
                strErr1 = "";
            }
            break;        
        case 'd':
        case 'D':
            // вправо
            if (2 * index + 2 > (size - 1))
                strErr1 = "Ошибка! Отсутствует правый потомок";
            else {
                index = 2 * index + 2;
                strErr1 = "";
            }
            break;
        case 'q':
        case 'Q':
            // выход
            return 0;        
        }
    }
    return 0;
}



// ***   Выбор массива   ***
int ArraySelection( int* arr1, int size1, 
                    int* arr2, int size2, 
                    int* arr3, int size3 ) {
    int intArray; 
    while (true) {
        // Очищаем консоль от прошлой игры
        system("cls");

        std::cout << "Добро пожаловать в навигатор по пирамиде!" << std::endl;
        std::cout << std::endl;
        std::cout << "1.  "; print_array(arr1, size1); std::cout << std::endl;
        std::cout << "2.  "; print_array(arr2, size2); std::cout << std::endl;
        std::cout << "3.  "; print_array(arr3, size3); std::cout << std::endl;
        std::cout << std::endl;
        std::cout << "Выберите массив: ";

        std::cin >> intArray;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intArray >= 1 && intArray <= 3) {
            return intArray;
        }
    }
    return 0;
}

// *** Итоговое меню   ***
int MenuFinal() {
    int intReplay;
    while (true) {
        // Очищаем консоль и повторяем вопрос
        system("cls");

        // Выводим меню
        //std::cout << std::endl;
        //std::cout << std::endl;
        std::cout << "1. Выбрать другой массив" << std::endl;
        std::cout << "2. Выйти" << std::endl;
        std::cout << "Выберите действие: ";

        std::cin >> intReplay;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (intReplay >= 1 && intReplay <= 2) {
            break;
        }
    }
    return intReplay;
}




// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Исходные данные
    int arr1[] = { 1, 3, 6, 5, 9, 8 };
    int arr2[] = { 94, 67, 18, 44, 55, 12, 6, 42 };
    int arr3[] = { 16, 11, 9, 10, 5, 6, 8, 1, 2, 4, };

    // Размеры массивов
    int size1 = sizeof(arr1) / sizeof(arr1[0]);
    int size2 = sizeof(arr2) / sizeof(arr2[0]);
    int size3 = sizeof(arr3) / sizeof(arr3[0]);


    // Создали класс параметров игры и временные переменные
    int intRun;
    int intReplay;
    int intArray;

    while (true) {
        // Инициируем объект
        intReplay = 0;

        // ***   Выбор массива   ***
        intArray = ArraySelection(arr1, size1, arr2, size2, arr3, size3 );

        // Запускаем движение по пирамиде
        if (intArray==1)
            travel(arr1, size1);
        else if (intArray == 2)
            travel(arr2, size2);
        else 
            travel(arr3, size3);
        
        // *** Итоговое меню   ***
        intReplay = MenuFinal();
        if (intReplay == 2) break;      // Выходим
    }

    std::cout << std::endl;
    //std::cout << "Игра завершена! Нажмите любую клавишу." << std::endl;
    std::cout << std::endl;


    system("pause");

    return EXIT_SUCCESS;
}

