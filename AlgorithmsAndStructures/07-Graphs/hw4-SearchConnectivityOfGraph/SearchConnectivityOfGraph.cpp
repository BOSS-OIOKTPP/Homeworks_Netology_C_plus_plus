#include <iostream>
#include <fstream>
#include <windows.h>

// Рекурсивная функция обхода графа в глубину
void dfs(int** graph, bool* visited, int current, int& count, int component, int* components) {
    // посетили текущую вершину
    visited[current] = true;
    // запомнили к какой компоненте связанности относится вершина
    components[current] = component;
    // ищим соседей, если не были в вершине, то заходим в нее 
    for (int i = 0; i < count; ++i)
        if (graph[current][i] == 1 && !visited[i] == true)
            dfs(graph, visited, i, count, component, components);
}



int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Подключаем файл
    std::ifstream inFile("in2.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл для чтения!" << std::endl;
        inFile.close();
        return 1;
    }

    // читаем размерность массива
    int count{};
    inFile >> count;

    // Создаем массив 
    int** graph = new int* [count];
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
    // Массив для хранения номеров компонентов связности для вершин
    int* components = new int[count] {0};  
    // Количество компонентов связности
    int componentCount = 0;


    // Обход графа для определения компонентов связности
    for (int i = 0; i < count; ++i) {
        if (!visited[i]) {
            componentCount++;
            dfs(graph, visited, i, count, componentCount, components);
        }
    }


    // Выводим результат
    std::cout << "Принадлежность вершин компонентам связности: ";
    for (int i = 0; i < count; ++i) 
        std::cout << i + 1 << " - " << components[i] << std::endl;    
    std::cout << "Количество компонентов связности в графе: " << componentCount << std::endl;


    // очищаем память   
    for (int i = 0; i < count; ++i)  delete graph[i];  // Удаляем строки массива    
    delete[] graph;     // Удаляем массив    
    delete[] visited;   // Удаляем массив    

    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

