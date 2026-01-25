#include "SearchServer.h"
#include "IniFile.h"  
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/algorithm/string.hpp>
#include <pqxx/pqxx>
#include <fstream>
#include <sstream>
#include <regex>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;

// === Вспомогательные функции ===

std::string urlDecode(const std::string& str) {
    std::string result;
    result.reserve(str.size());
    for (size_t i = 0; i < str.size(); ++i) {
        if (str[i] == '%' && i + 2 < str.size()) {
            unsigned int c;
            std::sscanf(str.substr(i + 1, 2).c_str(), "%x", &c);
            result += static_cast<char>(c);
            i += 2;
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
    std::string pattern = key + "=([^&]*)";
    std::regex re(pattern);
    std::smatch match;
    if (std::regex_search(body, match, re)) {
        return urlDecode(match[1].str());
    }
    return "";
}

// === Конструктор: используем IniFile ===

SearchServer::SearchServer(const std::string& configPath) {
    IniFile ini(configPath);

    // Читаем настройки сервера
    port_ = static_cast<unsigned short>(ini.getInt("Server", "Port", 8080));

    // Читаем настройки базы данных
    dbHost_ = ini.getString("Database", "Host", "localhost");
    dbPort_ = ini.getInt("Database", "Port", 5432);
    dbName_ = ini.getString("Database", "Name", "spider_db");
    dbUser_ = ini.getString("Database", "User", "spider_user");
    dbPass_ = ini.getString("Database", "Password", "");
}

// === Остальные методы без изменений ===

std::vector<std::string> SearchServer::parseQuery(const std::string& rawQuery) {
    std::string clean;
    for (char c : rawQuery) {
        if ((c >= 'a' && c <= 'z') ||
            (c >= 'A' && c <= 'Z') ||
            (c >= 'а' && c <= 'я') ||
            (c >= 'А' && c <= 'Я') ||
            c == ' ') {
            clean += c;
        }
    }

    std::vector<std::string> words;
    boost::split(words, clean, boost::is_space(), boost::token_compress_on);

    std::vector<std::string> validWords;
    for (auto& w : words) {
        boost::trim(w);
        boost::to_lower(w);
        if (w.size() >= 3 && validWords.size() < 4) {
            validWords.push_back(w);
        }
    }
    return validWords;
}

std::vector<SearchResult> SearchServer::searchInDatabase(const std::vector<std::string>& words) {
    if (words.empty()) return {};

    try {
        std::ostringstream connStr;
        connStr << "host=" << dbHost_
            << " port=" << dbPort_
            << " dbname=" << dbName_
            << " user=" << dbUser_
            << " password=" << dbPass_;

        pqxx::connection conn(connStr.str());
        pqxx::work txn(conn);

        std::string wordList;
        for (size_t i = 0; i < words.size(); ++i) {
            if (i > 0) wordList += ",";
            wordList += "'" + words[i] + "'";
        }

        std::ostringstream sql;
        sql << "SELECT v.url, SUM(w.frequency) AS total_freq "
            << "FROM visited_urls v "
            << "JOIN word_frequencies w ON w.url_id = v.id "
            << "WHERE w.word IN (" << wordList << ") "
            << "GROUP BY v.id, v.url "
            << "HAVING COUNT(DISTINCT w.word) = " << words.size() << " "
            << "ORDER BY total_freq DESC "
            << "LIMIT 10";

        pqxx::result res = txn.exec(sql.str());
        std::vector<SearchResult> results;
        for (const auto& row : res) {
            results.push_back({ row["url"].c_str(), row["total_freq"].as<int>() });
        }
        return results;
    }
    catch (const std::exception& e) {
        std::cerr << "DB Error: " << e.what() << std::endl;
        return {};
    }
}

std::string SearchServer::buildSearchForm() {
    return
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head><meta charset=\"utf-8\"><title>Поиск</title></head>\n"
        "<body>\n"
        "  <h2>Поисковая система</h2>\n"
        "  <form method=\"POST\" action=\"/search\">\n"
        "    <input type=\"text\" name=\"q\" placeholder=\"Введите запрос (до 4 слов)\" maxlength=\"100\" required>\n"
        "    <button type=\"submit\">Найти</button>\n"
        "  </form>\n"
        "</body>\n"
        "</html>";
}

std::string SearchServer::buildSearchResults(const std::vector<SearchResult>& results) {
    std::ostringstream html;
    html << "<!DOCTYPE html>\n"
        << "<html>\n"
        << "<head><meta charset=\"utf-8\"><title>Результаты поиска</title></head>\n"
        << "<body>\n"
        << "  <h2>Результаты поиска</h2>\n";

    if (results.empty()) {
        html << "  <p>По вашему запросу ничего не найдено.</p>\n";
    }
    else {
        html << "  <ol>\n";
        for (const auto& r : results) {
            html << "    <li><a href=\"" << r.url << "\">" << r.url << "</a> (релевантность: " << r.relevance << ")</li>\n";
        }
        html << "  </ol>\n";
    }

    html << "  <br><a href=\"/\">← Назад к поиску</a>\n"
        << "</body>\n"
        << "</html>";
    return html.str();
}

std::string SearchServer::buildErrorPage(const std::string& message) {
    return
        "<!DOCTYPE html>\n"
        "<html>\n"
        "<head><meta charset=\"utf-8\"><title>Ошибка</title></head>\n"
        "<body>\n"
        "  <h2>Ошибка сервера</h2>\n"
        "  <p>" + message + "</p>\n"
        "  <br><a href=\"/\">← Назад к поиску</a>\n"
        "</body>\n"
        "</html>";
}

void SearchServer::run() {
    boost::asio::io_context ioc{ 1 };
    tcp::acceptor acceptor{ ioc, {tcp::v4(), port_} };

    std::cout << "Сервер запущен на порту " << port_ << std::endl;

    for (;;) {
        tcp::socket socket{ ioc };
        acceptor.accept(socket);

        try {
            boost::beast::flat_buffer buffer;
            http::request<http::string_body> req;
            http::read(socket, buffer, req);

            http::response<http::string_body> res{ http::status::ok, req.version() };
            res.set(http::field::server, "SearchServer/1.0");
            res.set(http::field::content_type, "text/html; charset=utf-8");

            if (req.method() == http::verb::get && (req.target() == "/" || req.target() == "/search")) {
                res.body() = buildSearchForm();
            }
            else if (req.method() == http::verb::post && req.target() == "/search") {
                std::string query = extractQueryParam(req.body(), "q");
                if (query.empty()) {
                    res.body() = buildErrorPage("Пустой поисковый запрос.");
                }
                else {
                    auto words = parseQuery(query);
                    if (words.empty()) {
                        res.body() = buildErrorPage("Нет допустимых слов в запросе (минимум 3 символа).");
                    }
                    else {
                        auto results = searchInDatabase(words);
                        res.body() = buildSearchResults(results);
                    }
                }
            }
            else {
                res.result(http::status::not_found);
                res.body() = buildErrorPage("Страница не найдена.");
            }

            res.prepare_payload();
            http::write(socket, res);
        }
        catch (std::exception const& e) {
            std::cerr << "Ошибка: " << e.what() << std::endl;
        }
    }
}