#pragma once
#include <string>

class SpiderClient{
public:
    // Скачиваем HTML-страницу по URL (только HTTP, не HTTPS). Пример: fetch("http://example.com/path")    
    std::string fetch(const std::string& url);
private:
    // Внутренняя реализация с поддержкой редиректов
    std::string fetchImpl(const std::string& host, const std::string& target, unsigned short port, int max_redirects = 5);
};
