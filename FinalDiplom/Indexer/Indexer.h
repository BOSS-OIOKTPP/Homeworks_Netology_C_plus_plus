#pragma once
#include <string>
#include <unordered_map>
#include <vector>

class Indexer {
public:
    /// Обрабатывает HTML: удаляет теги, очищает текст, возвращает частоту слов.
    std::unordered_map<std::string, int> ProcessHtml(const std::string& html);

private:
    /// Удаляет HTML-теги с помощью простой логики (без регулярных выражений).
    std::string RemoveHtmlTags(const std::string& html);

    /// Очищает текст: оставляет только буквы и пробелы, приводит к нижнему регистру.
    std::string CleanText(const std::string& text);

    /// Разбивает текст на слова и фильтрует по длине (3–32 символа).
    std::vector<std::string> ExtractWords(const std::string& cleanText);
};