#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Indexer {
public:
    // Удаляем теги, очищаем текст, подсчитываем частоту слов
    std::unordered_map<std::string, int> ProcessHtml(const std::string& html);
private:
    // Удаляем теги
    std::string RemoveHtmlTags(const std::string& html);
    // Очищаем текст, оставляем только буквы и пробелы, приводим к нижнему регистру
    std::string CleanText(const std::string& text);
    // Выбираем слова из текста и фильтруем по длине от 3 до 32 символов
    std::vector<std::string> ExtractWords(const std::string& cleanText);
};