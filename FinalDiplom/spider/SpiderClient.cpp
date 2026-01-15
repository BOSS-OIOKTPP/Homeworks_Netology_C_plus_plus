#include "SpiderClient.h"
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <regex>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;

std::string SpiderClient::fetch(const std::string& url) {
    // Простой парсинг URL: http://host[:port][/path]
    std::regex url_regex(R"(^http://([^:/]+)(?::(\d+))?(/.*)?$)");
    std::smatch match;

    if (!std::regex_match(url, match, url_regex)) {
        throw std::runtime_error("Invalid URL format. Only HTTP supported: " + url);
    }

    std::string host = match[1].str();
    unsigned short port = match[2].matched ? static_cast<unsigned short>(std::stoi(match[2].str())) : 80;
    std::string target = match[3].matched ? match[3].str() : "/";

    return fetchImpl(host, target, port);
}

std::string SpiderClient::fetchImpl(const std::string& host, const std::string& target, unsigned short port) {
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
        if (res.result() != http::status::ok) {
            throw std::runtime_error("HTTP error: " + std::to_string(res.result_int()));
        }

        return beast::buffers_to_string(res.body().data());
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Fetch failed for " + host + ": " + e.what());
    }
}
