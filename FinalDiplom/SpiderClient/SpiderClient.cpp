#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <regex>
#include <iostream>
#include "SpiderClient.h"
#include "UrlUtils.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

std::string SpiderClient::fetch(const std::string& url) {
    // Простой парсинг URL: http://host[:port][/path]
    std::regex url_regex(R"(^http://([^:/]+)(?::(\d+))?(/.*)?$)");
    std::smatch match;

    if (!std::regex_match(url, match, url_regex)) 
        throw std::runtime_error("Недопустимый формат URL. Поддерживается только HTTP: " + url);    

    std::string host = match[1].str();
    unsigned short port = match[2].matched ? static_cast<unsigned short>(std::stoi(match[2].str())) : 80;
    std::string target = match[3].matched ? match[3].str() : "/";

    return fetchImpl(host, target, port);
}

std::string SpiderClient::fetchImpl(const std::string& host, const std::string& target, unsigned short port, int max_redirects)
{
    if (max_redirects < 0) {
        throw std::runtime_error("Слишком много редиректов");
    }

    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        beast::tcp_stream stream(ioc);

        // Разрешаем DNS
        auto const results = resolver.resolve(host, std::to_string(port));
        stream.connect(results);

        // Формируем HTTP-запрос
        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "KompasSpider/1.0");

        // Отправляем запрос
        http::write(stream, req);

        // Читаем ответ
        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;
        http::read(stream, buffer, res);

        // Закрываем соединение
        beast::error_code ec;
        stream.socket().shutdown(tcp::socket::shutdown_both, ec);

        // Проверяем статус
        switch (static_cast<int>(res.result())) {
        case 200: // OK
            break;

        case 301: // Moved Permanently
        case 302: // Found
        case 307: // Temporary Redirect
        case 308: // Permanent Redirect
        {
            auto location_it = res.find(http::field::location);
            if (location_it == res.end()) 
                throw std::runtime_error("Ответ с редиректом не содержит заголовок Location");            

            //std::string location_value = location_it->value().to_string();
            std::string location_value = static_cast<std::string>(location_it->value());
            std::string base_url = "http://" + host + target;
            std::string new_url = UrlUtils::MakeAbsolute(base_url, location_value);

            if (new_url.empty()) 
                throw std::runtime_error("Невозможно преобразовать Location в абсолютный URL: " + location_value);
            
            std::cout << " ↳ Редирект на: " << new_url << "\n";

            // Парсим новый URL и делаем рекурсивный вызов
            std::regex url_regex(R"(^http://([^:/]+)(?::(\d+))?(/.*)?$)");
            std::smatch match;
            if (!std::regex_match(new_url, match, url_regex)) {
                throw std::runtime_error("Недопустимый URL после редиректа: " + new_url);
            }

            std::string new_host = match[1].str();
            unsigned short new_port = match[2].matched ? static_cast<unsigned short>(std::stoi(match[2].str())) : 80;
            std::string new_target = match[3].matched ? match[3].str() : "/";

            return fetchImpl(new_host, new_target, new_port, max_redirects - 1);
        }

        default:
            throw std::runtime_error("HTTP ошибка: " + std::to_string(res.result_int()));
        }

        return beast::buffers_to_string(res.body().data());
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Не удалось выполнить выборку для " + host + ": " + e.what());
    }
}