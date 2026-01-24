#include "UrlUtils.h"
#include <regex>

// Функция преобразует относительный URL в абсолютный (поддерживает http и https)
std::string UrlUtils::MakeAbsolute(const std::string& base_url, const std::string& relative_url) {
    // Пропускаем пустые ссылки и якоря
    if (relative_url.empty() || relative_url[0] == '#') 
        return "";    

    // Абсолютные HTTP/HTTPS ссылки — оставляем как есть
    if (relative_url.substr(0, 7) == "http://" || relative_url.substr(0, 8) == "https://") 
        return relative_url;    

    // Протоколо-независимые ссылки //example.com → используем протокол базового URL
    if (relative_url.substr(0, 2) == "//") {
        if (base_url.substr(0, 8) == "https://") {
            return "https:" + relative_url;
        }
        else {
            return "http:" + relative_url;
        }
    }

    // Определяем протокол базового URL
    bool base_is_https = (base_url.substr(0, 8) == "https://");
    std::string protocol = base_is_https ? "https://" : "http://";

    // Парсим базовый URL
    std::regex baseRegex(R"(^(https?://)([^:/]+)(?::\d+)?(/.*)?$)");
    std::smatch baseMatch;
    if (!std::regex_match(base_url, baseMatch, baseRegex)) 
        return "";    

    std::string host = baseMatch[2].str();
    std::string basePath = baseMatch[3].matched ? baseMatch[3].str() : "/";

    // Абсолютный путь
    if (relative_url[0] == '/') 
        return protocol + host + relative_url;    

    // Относительный путь
    size_t lastSlash = basePath.rfind('/');
    if (lastSlash != std::string::npos) {
        return protocol + host + basePath.substr(0, lastSlash + 1) + relative_url;
    }
    return protocol + host + "/" + relative_url;
}