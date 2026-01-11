#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

// Размеры элементарного треугольника в символах
const int ELEM_WIDTH = 4;   // " /\ " + нулевой символ
const int ELEM_HEIGHT = 2;  // 2 строки

// Рисуем элементарный треугольник
void drawElement(vector<string>& canvas, int blockX, int blockY) {
    int x = blockX * ELEM_WIDTH;
    int y = blockY * ELEM_HEIGHT;

    // Первая строка: " /\ "
    canvas[y][x] = ' ';
    canvas[y][x + 1] = '/';
    canvas[y][x + 2] = '\\';
    canvas[y][x + 3] = ' ';

    // Вторая строка: "/__\"
    canvas[y + 1][x] = '/';
    canvas[y + 1][x + 1] = '_';
    canvas[y + 1][x + 2] = '_';
    canvas[y + 1][x + 3] = '\\';
}

// Рекурсивная функция построения треугольника Серпинского
void drawSierpinski(vector<string>& canvas, int level, int blockX, int blockY, int size) {
    if (level == 1) {
        // Базовый случай - рисуем элементарный треугольник
        drawElement(canvas, blockX, blockY);
        return;
    }

    // Новый размер (в блоках)
    int newSize = size / 2;

    // Рекурсивно рисуем 3 треугольника меньшего размера
    // Верхний треугольник
    drawSierpinski(canvas, level - 1, blockX + newSize, blockY, newSize);

    // Левый нижний треугольник
    drawSierpinski(canvas, level - 1, blockX, blockY + newSize, newSize);

    // Правый нижний треугольник
    drawSierpinski(canvas, level - 1, blockX + size, blockY + newSize, newSize);
}

// Создание и вывод треугольника Серпинского заданного уровня
void createSierpinskiTriangle(int level) {
    // Количество элементарных треугольников по каждой стороне
    int sizeInBlocks = pow(2, level - 1);

    // Размеры холста в символах
    int canvasWidth = sizeInBlocks * ELEM_WIDTH;
    int canvasHeight = sizeInBlocks * ELEM_HEIGHT;

    // Создаем холст
    vector<string> canvas(canvasHeight, string(canvasWidth, ' '));

    // Рисуем треугольник Серпинского
    drawSierpinski(canvas, level, 0, 0, sizeInBlocks);

    // Выводим результат
    for (const auto& row : canvas) {
        cout << row << endl;
    }
}

int main() {
    cout << "Треугольник Серпинского уровня 1:" << endl;
    createSierpinskiTriangle(1);

    cout << "\nТреугольник Серпинского уровня 2:" << endl;
    createSierpinskiTriangle(2);

    cout << "\nТреугольник Серпинского уровня 3:" << endl;
    createSierpinskiTriangle(3);

    cout << "\nТреугольник Серпинского уровня 4:" << endl;
    createSierpinskiTriangle(4);

    return 0;
}