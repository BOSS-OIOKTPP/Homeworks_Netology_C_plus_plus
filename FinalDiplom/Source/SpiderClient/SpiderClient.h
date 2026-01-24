#pragma once
#include <string>

class SpiderClient{
public:
    // Скачиваем HTML-страницу по URL (поддерживает http и https)
    std::string fetch(const std::string& url);
private:
    // Внутренняя реализация с поддержкой редиректов и HTTPS
    std::string fetchImpl(
        const std::string& host,
        const std::string& target,
        unsigned short port,
        bool is_https,
        int max_redirects = 5
    );    
};
