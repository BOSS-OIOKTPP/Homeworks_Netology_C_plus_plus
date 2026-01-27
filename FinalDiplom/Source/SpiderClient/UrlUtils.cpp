#include <string>
#include <vector>
#include <regex>
#include <charconv>
#include <boost/algorithm/string.hpp>
#include <boost/locale.hpp>
#include "UrlUtils.h"

namespace UrlUtils {

    std::string MakeAbsolute(const std::string& base_url, const std::string& relative_url) {
        if (relative_url.empty() || relative_url[0] == '#')
            return "";

        if (relative_url.substr(0, 7) == "http://")
            return relative_url;
        if (relative_url.substr(0, 8) == "https://")
            return relative_url;

        if (relative_url.substr(0, 2) == "//") {
            if (base_url.substr(0, 8) == "https://") {
                return "https:" + relative_url;
            }
            else {
                return "http:" + relative_url;
            }
        }

        bool base_is_https = (base_url.substr(0, 8) == "https://");
        std::string protocol = base_is_https ? "https://" : "http://";

        std::regex baseRegex(R"(^(https?://)([^:/]+)(?::\d+)?(/.*)?$)");
        std::smatch baseMatch;
        if (!std::regex_match(base_url, baseMatch, baseRegex))
            return "";

        std::string host = baseMatch[2].str();
        std::string basePath = baseMatch[3].matched ? baseMatch[3].str() : "/";

        if (relative_url[0] == '/')
            return protocol + host + relative_url;

        size_t lastSlash = basePath.rfind('/');
        if (lastSlash != std::string::npos) {
            return protocol + host + basePath.substr(0, lastSlash + 1) + relative_url;
        }
        return protocol + host + "/" + relative_url;
    }

    std::string urlDecode(const std::string& str) {
        std::string result;
        result.reserve(str.size());

        for (size_t i = 0; i < str.size(); ++i) {
            if (str[i] == '%' && i + 2 < str.size()) {
                char hex[3] = { str[i + 1], str[i + 2], '\0' };
                unsigned int value = 0;
                auto [ptr, ec] = std::from_chars(hex, hex + 2, value, 16);
                if (ec == std::errc{}) {
                    result += static_cast<char>(value);
                    i += 2;
                }
                else {
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

    std::string extractQueryParam(const std::string& body, const std::string& key) {
        std::regex re(key + "=([^&]*)");
        std::smatch match;
        if (std::regex_search(body, match, re)) {
            return urlDecode(match[1].str());
        }
        return "";
    }

    std::vector<std::string> UrlUtils::parseSearchQuery(const std::string& raw) {
        // Создаём локаль один раз (статически)
        static boost::locale::generator gen;
        static auto loc = gen("UTF-8");

        std::string cleaned;
        for (char c : raw) {
            if (c == ' ' || c == '\t' || c == '\n' || c == '\r') {
                cleaned += ' ';
            }
            else if (static_cast<unsigned char>(c) >= 128 ||  // часть UTF-8 символа (кириллица и др.)
                (c >= 'a' && c <= 'z') ||
                (c >= 'A' && c <= 'Z')) {
                cleaned += c;
            }
            // всё остальное (цифры, пунктуация, спецсимволы) — отбрасываем
        }

        // Приводим к нижнему регистру с поддержкой UTF-8
        cleaned = boost::locale::to_lower(cleaned, loc);

        // Разбиваем на слова
        std::vector<std::string> words;
        boost::split(words, cleaned, boost::is_space(), boost::token_compress_on);

        // Фильтруем по длине и количеству
        std::vector<std::string> valid;
        for (auto& w : words) {
            boost::trim(w);
            if (w.size() >= 3 && valid.size() < 4) {
                valid.push_back(w);
            }
        }
        return valid;
    }


    //std::vector<std::string> parseSearchQuery(const std::string& raw) {
    //    std::string clean;
    //    for (char c : raw) {
    //        if ((c >= 'a' && c <= 'z') ||
    //            (c >= 'A' && c <= 'Z') ||
    //            (c >= 'а' && c <= 'я') ||
    //            (c >= 'А' && c <= 'Я') ||
    //            c == ' ') {
    //            clean += c;
    //        }
    //    }

    //    std::vector<std::string> words;
    //    boost::split(words, clean, boost::is_space(), boost::token_compress_on);

    //    std::vector<std::string> valid;
    //    for (auto& w : words) {
    //        boost::trim(w);
    //        boost::to_lower(w);
    //        if (w.size() >= 3 && valid.size() < 4) {
    //            valid.push_back(w);
    //        }
    //    }
    //    return valid;
    //}

} // namespace UrlUtils