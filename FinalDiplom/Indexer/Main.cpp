#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "Indexer.h"


std::string ReadFile(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        throw std::runtime_error("Не удалось открыть файл: " + filename);
    }
    return std::string((std::istreambuf_iterator<char>(file)),
        std::istreambuf_iterator<char>());
}

int main() {
    // Установка кодировки консоли Windows    
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    try {
        // Пример 1: простой HTML
        std::string html1 = R"(
            <html>
            <body>
                <h1>Hello, World!</h1>
                <p>This is a <b>test</b> page with some words: hello, world, test, and more. А теперь на русском. Страница с несколькими словами: привет, мир, тест, тест и многое другое</p>
                <a href="/next">Next page</a>
            </body>
            </html>
        )";

        Indexer indexer;
        auto freq1 = indexer.ProcessHtml(html1);

        std::cout << "=== Test 1: Inline HTML ===\n";
        for (const auto& [word, count] : freq1) {
            std::cout << word << ": " << count << "\n";
        }

        // Пример 2: из файла
        std::cout << "\n=== Test 2: From file ===\n";
        std::string html2 = ReadFile("test.html");
        auto freq2 = indexer.ProcessHtml(html2);
        std::cout << "Всего уникальных слов: " << freq2.size() << "\n";
        int total = 0;
        for (const auto& [w, c] : freq2) total += c;
        std::cout << "Всего слов: " << total << "\n";

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }


    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

