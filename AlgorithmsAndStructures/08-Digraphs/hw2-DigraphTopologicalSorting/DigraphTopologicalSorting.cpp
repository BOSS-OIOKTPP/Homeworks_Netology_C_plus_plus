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
    std::ifstream inFile("in1.txt");
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



/*

#include <iostream>
#include <fstream>

// Рекурсивная функция для топологической сортировки (DFS)
void topologicalSortDFS(int** graph, bool* visited, int* order, int& orderIndex, int v, int n) {
    visited[v] = true;
    for (int i = 0; i < n; ++i) {
        if (graph[v][i] == 1 && !visited[i]) {
            topologicalSortDFS(graph, visited, order, orderIndex, i, n);
        }
    }
    order[orderIndex++] = v;  // Добавляем вершину в порядок
}

int main() {
    std::ifstream inFile("input.txt");
    if (!inFile.is_open()) {
        std::cerr << "Не удалось открыть файл!" << std::endl;
        return 1;
    }

    int n;
    inFile >> n;

    // Динамическое выделение памяти под матрицу смежности
    int** graph = new int*[n];
    for (int i = 0; i < n; ++i) {
        graph[i] = new int[n];
        for (int j = 0; j < n; ++j) {
            inFile >> graph[i][j];
        }
    }
    inFile.close();

    // Массив для отметки посещённых вершин
    bool* visited = new bool[n]{false};

    // Динамический массив для хранения топологического порядка
    int* order = new int[n];
    int orderIndex = 0;

    // Запускаем DFS для всех непосещённых вершин
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            topologicalSortDFS(graph, visited, order, orderIndex, i, n);
        }
    }

    // Выводим топологический порядок (в обратном порядке DFS)
    std::cout << "Топологическая сортировка: ";
    for (int i = n - 1; i >= 0; --i) {
        std::cout << order[i] + 1 << " ";  // +1, т.к. нумерация с 1
    }
    std::cout << std::endl;

    // Освобождаем память
    for (int i = 0; i < n; ++i) {
        delete[] graph[i];
    }
    delete[] graph;
    delete[] visited;
    delete[] order;

    return 0;
}

*/