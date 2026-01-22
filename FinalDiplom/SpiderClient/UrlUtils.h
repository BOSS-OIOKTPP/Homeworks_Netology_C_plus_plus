#pragma once
#include <string>

namespace UrlUtils {
    // Функция преобразует относительный URL в абсолютный (поддерживает http и https)
    std::string MakeAbsolute(const std::string& base_url, const std::string& relative_url);
}

