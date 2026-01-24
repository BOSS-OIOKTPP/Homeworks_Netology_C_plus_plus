#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/asio/ssl.hpp>
#include <regex>
#include <iostream>
#include "SpiderClient.h"
#include "UrlUtils.h"

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;
using tcp = net::ip::tcp;
using ssl_stream = beast::ssl_stream<beast::tcp_stream>;

// Глобальный SSL-контекст
static boost::asio::ssl::context make_ssl_context() {
    boost::asio::ssl::context ctx{ boost::asio::ssl::context::tlsv12_client };
    ctx.set_default_verify_paths();
    return ctx;
}

// Скачиваем HTML-страницу по URL (поддерживает http и https)
std::string SpiderClient::fetch(const std::string& url) {
    std::regex url_regex(R"(^(https?)://([^:/]+)(?::(\d+))?(/.*)?$)");
    std::smatch match;

    if (!std::regex_match(url, match, url_regex)) 
        throw std::runtime_error("Недопустимый формат URL. Поддерживается только HTTP/HTTPS: " + url);    

    std::string protocol = match[1].str();
    std::string host = match[2].str();
    unsigned short port = match[3].matched
        ? static_cast<unsigned short>(std::stoi(match[3].str()))
        : (protocol == "https" ? 443 : 80);
    std::string target = match[4].matched ? match[4].str() : "/";
    bool is_https = (protocol == "https");

    return fetchImpl(host, target, port, is_https);
}

// Внутренняя реализация с поддержкой редиректов и HTTPS
std::string SpiderClient::fetchImpl(const std::string& host, const std::string& target, unsigned short port, bool is_https, int max_redirects) {
    if (max_redirects < 0) 
        throw std::runtime_error("Слишком много редиректов");    

    try {
        net::io_context ioc;
        tcp::resolver resolver(ioc);
        auto const results = resolver.resolve(host, std::to_string(port));

        http::request<http::string_body> req{ http::verb::get, target, 11 };
        req.set(http::field::host, host);
        req.set(http::field::user_agent, "KompasSpider/1.0");

        beast::flat_buffer buffer;
        http::response<http::dynamic_body> res;

        if (is_https) {
            static auto ssl_ctx = make_ssl_context(); 
            ssl_stream stream(ioc, ssl_ctx);
            stream.next_layer().connect(results);
            stream.handshake(ssl_stream::handshake_type::client);
            http::write(stream, req);
            http::read(stream, buffer, res);
            beast::error_code ec;
            stream.shutdown(ec);
        }
        else {
            beast::tcp_stream stream(ioc);
            stream.connect(results);
            http::write(stream, req);
            http::read(stream, buffer, res);
            beast::error_code ec;
            stream.socket().shutdown(tcp::socket::shutdown_both, ec);
        }

        // Проверяем статус
        switch (static_cast<int>(res.result())) {
        case 200:
            break;

        case 301: case 302: case 307: case 308: {
            auto location_it = res.find(http::field::location);
            if (location_it == res.end()) {
                throw std::runtime_error("Ответ с редиректом не содержит заголовок Location");
            }

            std::string location_value = static_cast<std::string>(location_it->value());
            std::string base_url = (is_https ? "https://" : "http://") + host + target;
            std::string new_url = UrlUtils::MakeAbsolute(base_url, location_value);

            if (new_url.empty()) {
                throw std::runtime_error("Невозможно преобразовать Location в абсолютный URL: " + location_value);
            }

            std::cout << "Редирект на: " << new_url << "\n";

            // Рекурсивный вызов с новым URL
            std::regex url_regex(R"(^(https?)://([^:/]+)(?::(\d+))?(/.*)?$)");
            std::smatch match;
            if (!std::regex_match(new_url, match, url_regex)) {
                throw std::runtime_error("Недопустимый URL после редиректа: " + new_url);
            }

            std::string new_protocol = match[1].str();
            std::string new_host = match[2].str();
            unsigned short new_port = match[3].matched
                ? static_cast<unsigned short>(std::stoi(match[3].str()))
                : (new_protocol == "https" ? 443 : 80);
            std::string new_target = match[4].matched ? match[4].str() : "/";
            bool new_is_https = (new_protocol == "https");

            return fetchImpl(new_host, new_target, new_port, new_is_https, max_redirects - 1);
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