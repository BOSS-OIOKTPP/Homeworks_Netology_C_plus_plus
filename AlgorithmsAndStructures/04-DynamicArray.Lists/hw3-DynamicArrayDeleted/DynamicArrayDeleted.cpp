#include <iostream>
#include <string>
#include <windows.h>

void print_dynamic_array(int* arr, int logical_size, int actual_size) {
    for (int i = 0; i < logical_size; ++i)              std::cout << arr[i] << " ";
    for (int i = logical_size; i < actual_size; ++i)    std::cout << "_" << " ";
}

// ГЛАВНАЯ ПРОГРАММА
int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    
    int actual_size{ 0 };
    int logical_size{ 0 };
    int* arr;
    int* tmpArray;

    while (true) {
        // Очищаем консоль 
        system("cls");

        std::cout << "Введите фактичеcкий размер массива: ";
        std::cin >> actual_size;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (actual_size > 0 ) break;
    }

    while (true) {
        std::cout << "Введите логичеcкий размер массива: ";
        std::cin >> logical_size;
        if (!std::cin) {
            std::cout << "Ошибка! Введите целое число в диапазоне [1; " << actual_size << "]!" << std::endl << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
            continue;  // Пропускаем итерацию
        }

        if (logical_size > 0 && logical_size <= actual_size) 
            break;

        if (logical_size > actual_size) 
            std::cout << "Ошибка! Логический размер массива не может превышать фактический!" << std::endl << std::endl;        

        if (logical_size <= 0) 
            std::cout << "Ошибка! Логический размер массива не может быть меньше 1!" << std::endl << std::endl;        
    }

    // Создаем массив
    arr = new int[actual_size];

    // Вводим новые значения
    int i=0;
    while (i < logical_size) {
        int tmp{ 0 };
        std::cout << "Введите arr[" << i << "]: ";
        std::cin >> tmp;
        if (!std::cin) {
            std::cout << "Ошибка! Введите целое число!" << std::endl;
            std::cin.clear();
            std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки            
            continue;
        }
        arr[i] = tmp;
        i++;
    }    

    // Выводим на экран результат
    std::cout << "Динамический массив: ";
    print_dynamic_array(arr, logical_size, actual_size);
    std::cout << std::endl;
     
    // Вводим элемент для добавления
    while (true) {
        int tmp{ 0 };
        std::cout << "Удалить первый элемент? 1-да";
        std::cin >> tmp;
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки
        
        // выход из цикла и программы
        if (tmp != 1) {
            // Выводим на экран результат
            std::cout << "Спасибо! Ваш массив: ";
            print_dynamic_array(arr, logical_size, actual_size);
            std::cout << std::endl;
            break;
        }

        // 
        if (tmp == 1) {
            int logical_size_new = logical_size - 1;

            if (logical_size_new == -1) {
                std::cout << "Невозможно удалить первый элемент, так как массив пустой. До свидания!" << std::endl;
                break;
            }

            // если логический размер массива, уменьшенный на единицу, строго больше одной трети фактического размера, 
            // то сдвигаем все элементы массива, кроме первого, влево на 1
            if (logical_size_new == 0) {
                // логический размер уменьшится ниже
            }
            else if (logical_size_new > actual_size / 3) {
                for (int i = 1; i < logical_size_new; ++i) 
                    arr[i - 1] = arr[i];
            } 
            // если логический размер массива, уменьшенный на единицу, меньше или равен одной трети его фактического размера, 
            // тогда создаём новый массив размером в 3 раза меньше. В него перекладываем элементы из старого массива, 
            // кроме первого, со сдвигом индекса на 1 влево. Фактический и логический размеры массива изменяют своё значение.
            else {
                // уменьшаем фактический размер в 3 раза
                actual_size /= 3;
                // создаем новый массив
                tmpArray = new int[actual_size];
                // копируем данные в новый массив
                for (int i = 0; i < logical_size_new; ++i)
                    tmpArray[i] = arr[i];
                // удаляем старый массив
                delete[] arr;
                // запоминаем ссылку на новый массив
                arr = tmpArray;
            }
            // запоминаем новый логический размер 
            logical_size = logical_size_new;
        }
        
        // Выводим на экран результат
        std::cout << "Динамический массив: ";
        print_dynamic_array(arr, logical_size, actual_size);
        std::cout << std::endl;
    }

    // Удаляем массив
    delete[] arr;
 
    //std::cout << std::endl;
    //std::cout << "Нажмите любую клавишу для завершения программы." << std::endl;
    std::cout << std::endl;

    system("pause");

    return EXIT_SUCCESS;
}

