#include <iostream>
#include <fstream>
#include <windows.h>

// Рекурсивная функция обхода графа в глубину
bool dfs(int** graph, bool* visited, int current, int& count, int parent, bool& hasCycle) {
    // посетили текущую вершину
    visited[current] = true;
    std::cout << current + 1 << " ";  // т.к. current это индекс в массиве, по-этому добавляем +1, чтобы получить номер вершины
    // ищим соседей, если не были в вершине, то заходим в нее 
    for (int i = 0; i < count; ++i) 
        if (graph[current][i] == 1) {
            if (!visited[i] == true) {
                // если нашли цикл, то выходим из рекурсии
                if (dfs(graph, visited, i, count, current, hasCycle) == true)
                    return true;
            }
            // Если сосед посещён и не является родителем - это цикл
            else if (i != parent) {
                std::cout << i + 1 << " ";  // добавляем вершину, чтобы визуально увидеть цикл при выводе обхода графа
                hasCycle = true;
                return true;
            }
        }
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
    
    // Цикл по умолчанию не найден
    bool hasCycle = false;

    // Выполняем обход вершин
    std::cout << "Порядок обхода вершин: ";
    dfs(graph, visited, 0, count, -1, hasCycle);
    
    // Выводим сообщение о наличии цикла в графе
    std::cout << std::endl;
    if (hasCycle)
        std::cout << "В графе есть цикл!" << std::endl;
    else 
        std::cout << "В графе нет циклов" << std::endl;
    

    // очищаем память   
    for (int i = 0; i < count; ++i)  delete graph[i];  // Удаляем строки массива    
    delete[] graph;     // Удаляем массив    
    delete[] visited;   // Удаляем массив    

    std::cout << std::endl; 
    system("pause");

    return EXIT_SUCCESS;
}

