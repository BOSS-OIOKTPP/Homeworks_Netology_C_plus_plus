#pragma once
#include <string>

class SpiderClient{
public:
    // Скачивает HTML-страницу по URL (только HTTP, не HTTPS)
    // Пример: fetch("http://example.com/path")
    std::string fetch(const std::string & url);

private:
    std::string fetchImpl(const std::string& host, const std::string& target, unsigned short port = 80);
};
