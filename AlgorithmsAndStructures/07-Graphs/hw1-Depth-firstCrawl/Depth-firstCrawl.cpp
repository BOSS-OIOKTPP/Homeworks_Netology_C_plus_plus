#include <iostream>
#include <fstream>
#include <windows.h>

// Рекурсивная функция обхода графа в глубину
void dfs(int** graph, bool* visited, int current, int& count) {
    // посетили текущую вершину
    visited[current] = true;
    std::cout << current + 1 << " ";  // т.к. current это индекс в массиве, по-этому добавляем +1, чтобы получить номер вершины
    // ищим соседей, если не были в вершине, то заходим в нее 
    for (int i = 0; i < count; ++i) 
        if (graph[current][i] == 1 && !visited[i]==true) 
            dfs(graph, visited, i, count);    
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
    
    // Массив для отметки посещённых вершин
    bool* visited = new bool[count] {false};


    std::cout << "Порядок обхода вершин: ";

    // Выполняем обход вершин
    dfs(graph, visited, 0, count);



    // очищаем память   
    for (int i = 0; i < count; ++i)  delete graph[i];  // Удаляем строки массива    
    delete[] graph;     // Удаляем массив    
    delete[] visited;   // Удаляем массив    

    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

