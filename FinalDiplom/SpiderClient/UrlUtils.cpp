#include "UrlUtils.h"
#include <regex>

// Функция преобразует относительный URL в абсолютный
std::string UrlUtils::MakeAbsolute(const std::string& base_url, const std::string& relative_url) {
    // Пропускаем пустые ссылки и якоря
    if (relative_url.empty() || relative_url[0] == '#') {
        return "";
    }

    // Абсолютные HTTP-ссылки — оставляем как есть
    if (relative_url.substr(0, 7) == "http://") {
        return relative_url;
    }

    // HTTPS игнорируем
    if (relative_url.substr(0, 8) == "https://") {
        return "";
    }

    // Протоколо-независимые ссылки   //example.com → http://example.com
    if (relative_url.substr(0, 2) == "//") {
        return "http:" + relative_url;
    }

    // Парсим базовый URL
    std::regex baseRegex(R"(^http://([^:/]+)(?::\d+)?(/.*)?$)");
    std::smatch baseMatch;
    if (!std::regex_match(base_url, baseMatch, baseRegex)) {
        return "";
    }

    std::string host = baseMatch[1].str();
    std::string basePath = baseMatch[2].matched ? baseMatch[2].str() : "/";

    // Абсолютный путь
    if (relative_url[0] == '/') {
        return "http://" + host + relative_url;
    }

    // Относительный путь
    size_t lastSlash = basePath.rfind('/');
    if (lastSlash != std::string::npos) {
        return "http://" + host + basePath.substr(0, lastSlash + 1) + relative_url;
    }
    return "http://" + host + "/" + relative_url;
}