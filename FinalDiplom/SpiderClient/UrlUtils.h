#pragma once
#include <string>

namespace UrlUtils {
    // Функция преобразует относительный URL в абсолютный
    std::string MakeAbsolute(const std::string& base_url, const std::string& relative_url);
}

