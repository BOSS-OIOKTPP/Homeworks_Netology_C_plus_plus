#pragma once
#include <string>
#include <vector>

// Извлекаем абсолютные HTTP-ссылки из HTML-страницы
class LinkExtractor {
public:
    // Извлекаем все ссылки <a href="..."> из HTML
    // @param html - HTML-контент страницы
    // @param base_url - базовый URL страницы (для преобразования относительных ссылок)
    // @return вектор абсолютных URL (только http://, без дубликатов)
    static std::vector<std::string> Extract(const std::string& html, const std::string& base_url);
private:
    // Преобразуем относительный URL в абсолютный
    static std::string NormalizeUrl(const std::string& base_url, const std::string& href);

    // Проверяем, является ли URL допустимым (http://, не якорь, не пустой)
    static bool IsValidUrl(const std::string& url);
};

