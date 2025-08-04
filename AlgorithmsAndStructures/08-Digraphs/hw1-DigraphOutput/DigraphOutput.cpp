#include <iostream>
#include <fstream>
#include <windows.h>



// проверяем у вершины есть ли исходящие рёбра
bool hasEdges(int** graph, int& count, int i) {    
    bool hasEdges = false;
    for (int j = 0; j < count; ++j) {
        if (graph[i][j] == 1) {
            hasEdges = true;
            break;
        }
    }
    return hasEdges;
}

// Выводим орграф
void PrintDigraph(int** graph, int& count){
    // Проходим по всем вершинам
    for (int i = 0; i < count; ++i) {
        std::cout << i + 1 << ": ";  // т.к. i это индекс в массиве, по-этому добавляем +1, чтобы получить номер вершины                
        // Выводим все смежные вершины
        if (hasEdges(graph, count, i) == true) {
            for (int j = 0; j < count; ++j)
                if (graph[i][j] == 1)
                    std::cout << j + 1 << " ";
        }
        else
            std::cout << "нет";        
        std::cout << std::endl;
    }
}


int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
    // Подключаем файл
    std::ifstream inFile("in.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл для чтения!" << std::endl;
        inFile.close();
        return 1;
    }

    // читаем размерность массива
    int count{};
    inFile >> count;

    // Создаем массив 
    int** graph = new int*[count];
    // Создаем строки массива
    for (int i = 0; i < count; ++i) 
        graph[i] = new int[count];

    // Заполняем массив
    for (int i = 0; i < count; i++) 
        for (int j = 0; j < count; ++j) 
            inFile >> graph[i][j];

    // Закрываем файл
    inFile.close();
    
    
    // Выполняем обход вершин
    PrintDigraph(graph, count);


    // очищаем память   
    for (int i = 0; i < count; ++i)  delete graph[i];  // Удаляем строки массива    
    delete[] graph;     // Удаляем массив    

    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

