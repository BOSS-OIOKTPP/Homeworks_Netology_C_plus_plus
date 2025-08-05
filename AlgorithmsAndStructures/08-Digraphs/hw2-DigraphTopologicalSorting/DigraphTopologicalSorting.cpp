#include <iostream>
#include <fstream>
#include <windows.h>


// Рекурсивная функция обхода графа в глубину
// int** graph          -   матрица смежности 
// int& count_graph     -   размер матрицы смежности
// int current_graph    -   текущий индекс в матрице смежности
// VisitedInfo* visited -   массив посещенных вершин с индексом посещения 
// int& index_sort      -   индекс посещения вершины
void dfs(int** graph, int& count_graph, int current_graph, int* visited, int& index_sort) {
    // посетили текущую вершину, поставили временную метку "в обработке" для защиты от циклов 
    visited[current_graph] = -2;    
    // ищим соседей, если не были в вершине, то заходим в нее 
    for (int i = 0; i < count_graph; ++i)
        if (graph[current_graph][i] == 1) {
            if (visited[i] == -2) {
                std::cerr << "Граф содержит цикл! Топологическая сортировка невозможна." << std::endl;
                exit(1);
            }
            else if (visited[i] == -1)
                dfs(graph, count_graph, i, visited, index_sort);
        }
    // запоминаем индекс посещения 
    visited[current_graph] = index_sort++;
}



int main()
{
    // Установка кодировки консоли Windows
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
   
    // Подключаем файл
    // in1.txt  9х9
    // in2.txt  6х6
    // in3.txt  9х9 цикл

    std::ifstream inFile("in1.txt");
    if (!inFile.is_open()) {
        std::cout << "Не удалось открыть файл для чтения!" << std::endl;
        inFile.close();
        return 1;
    }

    // читаем размерность массива
    int count{};
    inFile >> count;
    // читаем массив
    int** graph = new int*[count];                                   // Создаем массив 
    for (int i = 0; i < count; ++i)  graph[i] = new int[count];      // Создаем строки массива
    for (int i = 0; i < count; i++)  for (int j = 0; j < count; ++j) // Заполняем массив
        inFile >> graph[i][j];

    // Закрываем файл
    inFile.close();
    
    // Массив для отметки посещённых вершин
    int* visited = new int[count];
    for (int i = 0; i < count; ++i) 
        visited[i] = -1;    

    // Текущий индекс посещения
    int index_sort = 0;
    for (int i = 0; i < count; ++i) 
        if (visited[i]==-1) 
            dfs(graph, count, i, visited, index_sort);


    // Вывод топологической сортировки (в обратном порядке индексов)
    std::cout << "Топологическая сортировка: ";
    for (int pos = count - 1; pos >= 0; --pos) {
        for (int i = 0; i < count; ++i) {
            if (visited[i] == pos) {
                std::cout << i + 1 << " ";  // +1, т.к. нумерация с 1
                break;
            }
        }
    }
    std::cout << std::endl;


    // очищаем память   
    for (int i = 0; i < count; ++i)  delete graph[i];  // Удаляем строки массива    
    delete[] graph;     // Удаляем массив    
    delete[] visited;   // Удаляем массив    

    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}