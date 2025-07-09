#include <iostream>
#include <string>
#include "FibonacciTree.h"


// Функция для вычисления длины строки "F(n)"
int NodeWidth(int n) {
    std::string strF = "F(" + std::to_string(n) + ")";
    return strF.length();
}

// Функция для вычисления смещения между узлами
int calculateOffset(int n, int level) {
    // Базовое смещение (можно настроить под конкретный случай)
    int base_offset = 4;

    // Уменьшаем смещение с каждым уровнем
    return base_offset * (nodeWidth(n) + 1) / (level + 1);
}

// Рекурсивная функция отрисовки дерева
void drawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int rootPos = 0;

    // Вычисляем позицию корня при первом вызове
    if (isRoot) {
        rootPos = nodeWidth(n) * 2; // Начальное смещение
        pos = rootPos;
    }

    // Отрисовка текущего узла
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << std::endl;

    // Вычисляем смещение для дочерних узлов
    int offset = calculateOffset(n, level);

    // Отрисовка связей
    int left_pos = pos - offset;
    int right_pos = pos + offset;

    // Вычисляем позиции для "/" и "\"
    int slash_pos = pos - offset / 2;
    int backslash_pos = pos + offset / 2;

    std::cout << std::string(slash_pos, ' ') << "/";
    std::cout << std::string(backslash_pos - slash_pos - 1, ' ') << "\\" << std::endl;

    // Рекурсивная отрисовка поддеревьев
    drawFibTree(n - 1, level + 1, left_pos, false);
    drawFibTree(n - 2, level + 1, right_pos, false);
}



/*
// Функция для вычисления длины строки "F(n)"
int NodeWidth(int n) {
    std::string strF = "F(" + std::to_string(n) + ")";
    return strF.length();
}

// Функция для вычисления длины схлопнутой левой ветви  F(1) F(2) F(3) (F4) если n=4
// Используется для вычисления смещения главного узла в консоле
int CollapsedLeftWidth(int n) {
    if (n <= 1) return NodeWidth(n);
    return NodeWidth(n) + 1 + CollapsedLeftWidth(n - 1); // "F(n) " + предыдущие; 1 это дополнительный пробел
}

// Функция для рекурсивной отрисовки дерева
void DrawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int RootOffset = 0;   // Смещение главного узла

    // Вычисляем смещение главного узла при первом вызове
    if (isRoot) {
        RootOffset = CollapsedLeftWidth(n - 1);
        pos = RootOffset;
    }

    // Отрисовка текущего узла
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }
    std::cout << std::endl;

    // Вычисляем смещение для дочерних узлов
    int offset = pow(2, max(n - level, 1)); // Динамическое смещение

    // Отрисовка связей
    int left_pos = pos - offset / 2;
    int right_pos = pos + offset / 2;

    std::cout << std::string(left_pos + NodeWidth(n) / 2, ' ') << "/";
    std::cout << std::string(right_pos - left_pos - NodeWidth(n) + 1, ' ') << "\\" << std::endl;

    // Рекурсивная отрисовка поддеревьев
    DrawFibTree(n - 1, level + 1, left_pos, false);
    DrawFibTree(n - 2, level + 1, right_pos, false);
}
*/



