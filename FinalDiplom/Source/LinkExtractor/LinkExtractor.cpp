#include <regex>
#include <set>
#include "LinkExtractor.h"
#include "UrlUtils.h"

// Преобразуем относительный URL в абсолютный
std::string LinkExtractor::NormalizeUrl(const std::string& base_url, const std::string& href) {
    return UrlUtils::MakeAbsolute(base_url, href);
}

// Проверяем, является ли URL допустимым (http:// или https://, не якорь, не пустой)
bool LinkExtractor::IsValidUrl(const std::string& url) {
    if (url.empty()) return false;
    if (!url.starts_with("http://") && !url.starts_with("https://")) return false;
    return true;
}

// Извлекаем все ссылки <a href="..."> из HTML
std::vector<std::string> LinkExtractor::Extract(const std::string& html, const std::string& base_url) {
    std::regex linkRegex(R"(<a\s+[^>]*href\s*=\s*["']?([^"'>\s]+))", std::regex::icase);
    std::sregex_iterator it(html.begin(), html.end(), linkRegex);
    std::sregex_iterator end;

    std::set<std::string> uniqueUrls;

    for (; it != end; ++it) {
        std::string href = it->str(1);
        std::string url = NormalizeUrl(base_url, href);
        if (IsValidUrl(url))
            uniqueUrls.insert(url);
    }

    return std::vector<std::string>(uniqueUrls.begin(), uniqueUrls.end());
}