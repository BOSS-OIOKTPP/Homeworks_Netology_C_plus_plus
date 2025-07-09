#include <iostream>
#include <string>
#include "FibonacciTree.h"


// ������� ��� ���������� ����� ������ "F(n)"
int NodeWidth(int n) {
    std::string strF = "F(" + std::to_string(n) + ")";
    return strF.length();
}

// ������� ��� ���������� �������� ����� ������
int calculateOffset(int n, int level) {
    // ������� �������� (����� ��������� ��� ���������� ������)
    int base_offset = 4;

    // ��������� �������� � ������ �������
    return base_offset * (nodeWidth(n) + 1) / (level + 1);
}

// ����������� ������� ��������� ������
void drawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int rootPos = 0;

    // ��������� ������� ����� ��� ������ ������
    if (isRoot) {
        rootPos = nodeWidth(n) * 2; // ��������� ��������
        pos = rootPos;
    }

    // ��������� �������� ����
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }

    std::cout << std::endl;

    // ��������� �������� ��� �������� �����
    int offset = calculateOffset(n, level);

    // ��������� ������
    int left_pos = pos - offset;
    int right_pos = pos + offset;

    // ��������� ������� ��� "/" � "\"
    int slash_pos = pos - offset / 2;
    int backslash_pos = pos + offset / 2;

    std::cout << std::string(slash_pos, ' ') << "/";
    std::cout << std::string(backslash_pos - slash_pos - 1, ' ') << "\\" << std::endl;

    // ����������� ��������� �����������
    drawFibTree(n - 1, level + 1, left_pos, false);
    drawFibTree(n - 2, level + 1, right_pos, false);
}



/*
// ������� ��� ���������� ����� ������ "F(n)"
int NodeWidth(int n) {
    std::string strF = "F(" + std::to_string(n) + ")";
    return strF.length();
}

// ������� ��� ���������� ����� ���������� ����� �����  F(1) F(2) F(3) (F4) ���� n=4
// ������������ ��� ���������� �������� �������� ���� � �������
int CollapsedLeftWidth(int n) {
    if (n <= 1) return NodeWidth(n);
    return NodeWidth(n) + 1 + CollapsedLeftWidth(n - 1); // "F(n) " + ����������; 1 ��� �������������� ������
}

// ������� ��� ����������� ��������� ������
void DrawFibTree(int n, int level = 0, int pos = 0, bool isRoot = true) {
    static int RootOffset = 0;   // �������� �������� ����

    // ��������� �������� �������� ���� ��� ������ ������
    if (isRoot) {
        RootOffset = CollapsedLeftWidth(n - 1);
        pos = RootOffset;
    }

    // ��������� �������� ����
    std::cout << std::string(pos, ' ') << "F(" << n << ")";

    if (n <= 1) {
        std::cout << std::endl;
        return;
    }
    std::cout << std::endl;

    // ��������� �������� ��� �������� �����
    int offset = pow(2, max(n - level, 1)); // ������������ ��������

    // ��������� ������
    int left_pos = pos - offset / 2;
    int right_pos = pos + offset / 2;

    std::cout << std::string(left_pos + NodeWidth(n) / 2, ' ') << "/";
    std::cout << std::string(right_pos - left_pos - NodeWidth(n) + 1, ' ') << "\\" << std::endl;

    // ����������� ��������� �����������
    DrawFibTree(n - 1, level + 1, left_pos, false);
    DrawFibTree(n - 2, level + 1, right_pos, false);
}
*/



