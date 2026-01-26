#pragma once

#include <string>
#include <vector>

namespace UrlUtils {
    // Преобразует относительный URL в абсолютный (поддерживает http и https)
    std::string MakeAbsolute(const std::string& base_url, const std::string& relative_url);

    // Декодирует percent-encoded строку (например, %D0%BF%D1%80%D0%B8%D0%B2%D0%B5%D1%82)
    std::string urlDecode(const std::string& encoded);

    // Извлекает значение параметра из строки вида "q=привет+мир&lang=ru"
    std::string extractQueryParam(const std::string& queryBody, const std::string& key);

    // Очистка и парсинг поискового запроса
    std::vector<std::string> parseSearchQuery(const std::string& rawQuery);

}

