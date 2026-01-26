#include <boost/algorithm/string.hpp>
#include <regex>
#include <charconv>
#include "UrlUtils.h"


// Преобразует относительный URL в абсолютный (поддерживает http и https)
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

// Декодирует percent-encoded строку (например, %D0%BF%D1%80%D0%B8%D0%B2%D0%B5%D1%82)
std::string UrlUtils::urlDecode(const std::string& str) {
    std::string result;
    result.reserve(str.size());

    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '%' && i + 2 < str.size()) {
            // Проверяем, что следующие два символа — шестнадцатеричные цифры
            char hex[3] = { str[i + 1], str[i + 2], '\0' };
            unsigned int value = 0;

            auto [ptr, ec] = std::from_chars(hex, hex + 2, value, 16);
            if (ec == std::errc{}) {
                result += static_cast<char>(value);
                i += 2; // пропускаем два символа после '%'
            }
            else {
                // Если не удалось распарсить — оставляем как есть
                result += str[i];
            }
        }
        else if (str[i] == '+') {
            result += ' ';
        }
        else {
            result += str[i];
        }
    }
    return result;
}

// Извлекает значение параметра из строки вида "q=привет+мир&lang=ru"
std::string UrlUtils::extractQueryParam(const std::string& body, const std::string& key) {
    std::regex re(key + "=([^&]*)");
    std::smatch match;
    if (std::regex_search(body, match, re)) {
        return urlDecode(match[1].str());
    }
    return "";
}

// Очистка и парсинг поискового запроса
std::vector<std::string> UrlUtils::parseSearchQuery(const std::string& raw) {
    // 1. Оставляем только буквы и пробелы
    std::string clean;
    for (char c : raw) {
        // Проверяем: латиница, кириллица или пробел
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'а' && c <= 'я') ||
            (c >= 'А' && c <= 'Я') ||
            c == ' ') {
            clean += c;
        }
    }

    // 2. Разбиваем очищённую строку на отдельные слова по пробелам.
    //    boost::token_compress_on гарантирует, что несколько подряд идущих пробелов
    //    будут обработаны как один разделитель (избегаем пустых слов).
    std::vector<std::string> words;
    boost::split(words, clean, boost::is_space(), boost::token_compress_on);

    // 3. Формируем валидный список слов для поиска:
    //    - удаляем начальные и конечные пробелы (на всякий случай),
    //    - приводим слово к нижнему регистру (для корректного сравнения с индексом),
    //    - отбрасываем слова короче 3 символов,
    //    - ограничиваем общее количество слов до 4 (по условию задания).
    std::vector<std::string> valid;
    for (auto& w : words) {
        boost::trim(w);
        boost::to_lower(w);
        if (w.size() >= 3 && valid.size() < 4) {
            valid.push_back(w);
        }
    }
    return valid;
}