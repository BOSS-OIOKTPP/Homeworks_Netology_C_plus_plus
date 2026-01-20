#include "Indexer.h"
#include <boost/locale.hpp>


// Удаляем теги
std::string Indexer::RemoveHtmlTags(const std::string& html) {
    std::string result;
    bool inside_tag = false;

    for (char c : html) {
        if (c == '<') 
            inside_tag = true;
        else if (c == '>') 
            inside_tag = false;        
        else if (!inside_tag) 
            result += c;        
    }
    return result;
}

// Очищаем текст, оставляем только буквы и пробелы, приводим к нижнему регистру
std::string Indexer::CleanText(const std::string& text) {
    // Создаем локаль, чтобы обрабатывать русские буква в boost::locale::to_lower
    static boost::locale::generator gen;
    static auto loc = gen("UTF-8");

    // Создаем очищенную строку
    std::string cleaned;
    for (char c : text) {
        // Заменяем управляющие символы на пробелы
        if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
            cleaned += ' ';
        }
        // Латинские буквы, русские буквы и прочие символы, у которых код >128 запоминаем
        else if (static_cast<unsigned char>(c) >= 128 ||
            (c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z')) {
            cleaned += c;
        }
        // Остальные символы: цифры, пунктуация, спецсимволы - игнорируем 
    }
    return boost::locale::to_lower(cleaned, loc);
}

// Выбираем слова из текста и фильтруем по длине от 3 до 32 символов
std::vector<std::string> Indexer::ExtractWords(const std::string& cleanText) {
    std::vector<std::string> words;
    std::string word;

    for (char c : cleanText) {
        if (c == ' ') {
            if (!word.empty()) {
                if (word.size() >= 3 && word.size() <= 32) {
                    words.push_back(word);
                }
                word.clear();
            }
        }
        else {
            word += c;
        }
    }
    // Последнее слово
    if (!word.empty() && word.size() >= 3 && word.size() <= 32) 
        words.push_back(word);
    
    return words;
}

// Удаляем теги, очищаем текст, подсчитываем частоту слов
std::unordered_map<std::string, int> Indexer::ProcessHtml(const std::string& html) {
    std::string noTags = RemoveHtmlTags(html);
    std::string clean = CleanText(noTags);
    std::vector<std::string> words = ExtractWords(clean);

    // Подсчитываем слова
    std::unordered_map<std::string, int> freq;
    for (const auto& w : words) 
        freq[w]++;    

    return freq;
}