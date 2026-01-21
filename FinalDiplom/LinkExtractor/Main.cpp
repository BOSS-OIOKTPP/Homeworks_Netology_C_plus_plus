#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include "LinkExtractor.h"


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
        // Тест 1: простой HTML
        std::string html1 = R"(
            <html>
            <body>
                <a href="/page1">Page 1</a>
                <a href="page2.html">Page 2</a>
                <a href="http://example.com/external">External</a>
                <a href="https://secure.com">HTTPS (ignored)</a>
                <a href="#section">Anchor (ignored)</a>
                <a href="//cdn.example.com/script.js">Protocol-relative</a>
            </body>
            </html>
        )";

        std::string base_url = "http://test.com/folder/index.html";
        auto links1 = LinkExtractor::Extract(html1, base_url);

        std::cout << "=== Тест 1: Встроенный HTML ===\n";
        for (const auto& link : links1) {
            std::cout << link << "\n";
        }

        // Тест 2: из файла
        std::cout << "\n=== Тест 2: Из файла ===\n";
        std::string html2 = ReadFile("test.html");
        auto links2 = LinkExtractor::Extract(html2, "http://info.cern.ch/");
        std::cout << "Found " << links2.size() << " links:\n";
        for (const auto& link : links2) {
            std::cout << link << "\n";
        }

    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << "\n";
        return 1;
    }

    std::cout << std::endl;
    system("pause");

    return EXIT_SUCCESS;
}

