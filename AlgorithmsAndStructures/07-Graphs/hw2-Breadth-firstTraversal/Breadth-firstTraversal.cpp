#include <iostream>
#include <fstream>
#include <windows.h>


// Функция обхода графа в ширину
void bfs(int** graph, int count, int start) {
    // Массив для отметки посещённых вершин
    bool* visited = new bool[count] {false};

    // Динамический массив для реализации очереди
    int* queue   = new int[count];
    int idxBegin = 0;   // Индекс начала очереди
    int idxEnd   = 0;     // Индекс конца очереди

    // Начинаем обход с выбранной вершины
    int idxStart      = start - 1;    
    queue[idxEnd++]   = idxStart;
    visited[idxStart] = true;

    while (idxBegin < idxEnd) {
        int current = queue[idxBegin++];
        std::cout << current + 1 << " ";  // т.к. current это индекс в массиве, по-этому добавляем +1, чтобы получить номер вершины

        // Добавляем всех непосещённых соседей в очередь
        for (int i = 0; i < count; ++i) {
            if (graph[current][i] == 1 && !visited[i] == true) {
                visited[i] = true;
                queue[idxEnd++] = i;
            }
        }
    }

    // Освобождаем память
    delete[] visited;
    delete[] queue;
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
    
    // Запрашиваем начальную вершину
    int start;    
    while (true) {
        std::cout << "В графе " << count << " вершин. Введите номер вершины, с которой начнётся обход: ";
        std::cin >> start;
        std::cin.clear(); // Сбрасываем флаги ошибок, например, если ввели букву
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очищаем буфер до символа новой строки

        if (start>=1 && start<=count)
            break;
        else
            std::cout << "Ошибка: неверный номер вершины!" << std::endl;
    }

    std::cout << "Порядок обхода вершин: ";

    // Выполняем обход вершин
    bfs(graph, count, start);

    // очищаем память   
    for (int i = 0; i < count; ++i) 
        delete graph[i];  // Удаляем строки массива    
    delete[] graph;       // Удаляем массив
    

    std::cout << std::endl << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

