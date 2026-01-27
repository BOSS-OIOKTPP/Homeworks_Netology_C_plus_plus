#include <iostream>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <windows.h>
#include "DatabaseManager.h"
#include "IniFile.h"
#include "UrlUtils.h"

using tcp = boost::asio::ip::tcp;
namespace http = boost::beast::http;


//Формирует HTML - страницу с простой поисковой формой
std::string buildSearchForm();
//Формирует HTML - страницу с результатами поиска
std::string buildResultsPage(const std::vector<std::pair<std::string, int>>& results);
// Формирует HTML-страницу с сообщением об ошибке
std::string buildErrorPage(const std::string& message);



int main() {
    // Установка кодировки консоли Windows
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8); // 65001

    
    try {
        // 1. Читаем конфигурацию
        IniFile config("config.ini");

        // 2. Настройки сервера
        unsigned short port = static_cast<unsigned short>(config.readInteger("Server", "Port", 8080) );

        // 3. Настройки БД
        std::string host = config.readString("Database", "Host", "localhost");
        std::string dbport = config.readString("Database", "Port", "5432");
        std::string name = config.readString("Database", "Name", "spider_db");
        std::string user = config.readString("Database", "User", "spider_user");
        std::string pass = config.readString("Database", "Password", "");

        std::string connection_string =
            "host=" + host + " " +
            "port=" + dbport + " " +
            "dbname=" + name + " " +
            "user=" + user + " " +
            "password=" + pass;

        // 4. Подключаемся к БД
        DatabaseManager db(connection_string);
        db.Connect(); // убедимся, что подключение работает

        std::cout << "Сервер запущен на порту " << port << "\n";

        // 5. Запускаем HTTP-сервер
        boost::asio::io_context ioc{ 1 };
        tcp::acceptor acceptor{ ioc, {tcp::v4(), port} };

        // 6. Бесконечный цикл ожидания входящих подключений
        for (;;) {
            // 6.1. Принимаем новое TCP-соединение от клиента (браузера)
            tcp::socket socket{ ioc };
            acceptor.accept(socket);

            try {
                // 6.2. Буфер для хранения входящих данных HTTP-запроса
                boost::beast::flat_buffer buffer;

                // 6.3. Объект запроса: парсит данные из буфера в структуру HTTP-запроса
                http::request<http::string_body> req;
                http::read(socket, buffer, req);

                // 6.4. Создаём HTTP-ответ с кодом 200 OK и той же версией HTTP, что и запрос
                http::response<http::string_body> res{ http::status::ok, req.version() };

                // 6.5. Устанавливаем заголовки ответа:
                //      - Server: идентификатор сервера (для отладки),
                //      - Content-Type: указываем, что тело ответа — HTML в кодировке UTF-8.
                res.set(http::field::server, "SearchServer/1.0");
                res.set(http::field::content_type, "text/html; charset=utf-8");

                // 6.6. Обработка GET-запроса к корню или /search — показываем форму поиска
                if (req.method() == http::verb::get &&
                    (req.target() == "/" || req.target() == "/search")) {
                    res.body() = buildSearchForm();
                }
                // 6.7. Обработка POST-запроса к /search — выполняем поиск
                else if (req.method() == http::verb::post && req.target() == "/search") {
                    // 6.7.1. Извлекаем значение параметра 'q' из тела POST-запроса (например, q=привет+мир)
                    std::string rawQuery = UrlUtils::extractQueryParam(req.body(), "q");

                    // 6.7.2. Проверяем, не пуст ли запрос
                    if (rawQuery.empty()) {
                        res.body() = buildErrorPage("Пустой поисковый запрос.");
                    }
                    else {
                        // 6.7.3. Очищаем и парсим запрос: оставляем только слова (≥3 символов), не более 4
                        auto words = UrlUtils::parseSearchQuery(rawQuery);
                        if (words.empty()) {
                            res.body() = buildErrorPage("Нет допустимых слов (минимум 3 символа).");
                        }
                        else {
                            // 6.7.5. Выполняем поиск в базе данных: находим URL, содержащие ВСЕ слова,
                            //        ранжируя по суммарной частоте упоминаний
                            auto results = db.searchWords(words);

                            // 6.7.6. Формируем HTML-страницу с результатами (или сообщением "ничего не найдено")
                            res.body() = buildResultsPage(results);
                        }
                    }
                }
                // 6.8. Любой другой запрос (например, /favicon.ico) считаем ошибкой 404
                else {
                    res.result(http::status::not_found);
                    res.body() = buildErrorPage("Страница не найдена.");
                }

                // 6.9. Автоматически вычисляем и устанавливаем заголовок Content-Length
                res.prepare_payload();

                // 6.10. Отправляем сформированный HTTP-ответ клиенту (браузеру)
                http::write(socket, res);
            }
            // 6.11. Локальная обработка ошибок при обработке одного запроса
            //       (например, повреждённый HTTP-запрос, сетевая ошибка)
            catch (const std::exception& e) {
                std::cerr << "Ошибка обработки запроса: " << e.what() << "\n";
                // Соединение закроется автоматически при выходе из блока
            }
        }
    }
    catch (const std::exception& e) {
        std::cerr << "Критическая ошибка: " << e.what() << "\n";
        return 1;
    }

    // std::cout << std::endl;
    // system("pause");

    return EXIT_SUCCESS;
}


// Простой вариант
//std::string buildSearchForm() {
//    return
//        "<!DOCTYPE html>\n"
//        "<html lang=\"ru\">\n"
//        "<head>\n"
//        "  <meta charset=\"utf-8\">\n"
//        "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
//        "  <title>Поиск</title>\n"
//        "</head>\n"
//        "<body>\n"
//        "  <h2>Поисковая система</h2>\n"
//        "  <form method=\"POST\" action=\"/search\">\n"
//        "    <input type=\"text\" name=\"q\" placeholder=\"Введите запрос (до 4 слов)\" maxlength=\"100\" required>\n"
//        "    <button type=\"submit\">Найти</button>\n"
//        "  </form>\n"
//        "</body>\n"
//        "</html>";
//}

// Поле поиска — в 3 раза шире и в 2 раза выше,
// центрирована по горизонтали и вертикали,
// кнопка «Найти» — внутри поля(как у Google)
std::string buildSearchForm() {
    return
        "<!DOCTYPE html>\n"
        "<html lang=\"ru\">\n"
        "<head>\n"
        "  <meta charset=\"utf-8\">\n"
        "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
        "  <title>Поиск</title>\n"
        "  <style>\n"
        "    body {\n"
        "      margin: 0;\n"
        "      padding: 0;\n"
        "      height: 100vh;\n"
        "      display: flex;\n"
        "      justify-content: center;\n"
        "      align-items: center;\n"
        "      background: #fff;\n"
        "      font-family: Arial, sans-serif;\n"
        "    }\n"
        "    .search-container {\n"
        "      text-align: center;\n"
        "    }\n"
        "    .search-box {\n"
        "      width: 564px;       /* Примерно в 3 раза шире стандартного (~188px) */\n"
        "      height: 44px;       /* В 2 раза выше стандартного (~22px) */\n"
        "      padding: 0 20px;\n"
        "      font-size: 16px;\n"
        "      border: 1px solid #dfe1e5;\n"
        "      border-radius: 24px;\n"
        "      outline: none;\n"
        "      box-shadow: 0 1px 6px rgba(32,33,36,.28);\n"
        "    }\n"
        "    .search-box:focus {\n"
        "      box-shadow: 0 1px 10px rgba(32,33,36,.28);\n"
        "    }\n"
        "    .search-button {\n"
        "      margin-top: 20px;\n"
        "      padding: 10px 20px;\n"
        "      font-size: 14px;\n"
        "      background-color: #f8f9fa;\n"
        "      border: 1px solid #f8f9fa;\n"
        "      border-radius: 4px;\n"
        "      cursor: pointer;\n"
        "    }\n"
        "    .search-button:hover {\n"
        "      box-shadow: 0 1px 1px rgba(0,0,0,.1);\n"
        "      background-color: #f1f3f4;\n"
        "    }\n"
        "    h2 {\n"
        "      color: #202124;\n"
        "      margin-bottom: 30px;\n"
        "    }\n"
        "  </style>\n"
        "</head>\n"
        "<body>\n"
        "  <div class=\"search-container\">\n"
        "    <h2>Поисковая система</h2>\n"
        "    <form method=\"POST\" action=\"/search\">\n"
        "      <input type=\"text\" name=\"q\" class=\"search-box\" placeholder=\"Введите запрос (до 4 слов)\" maxlength=\"100\" required>\n"
        "      <br>\n"
        "      <button type=\"submit\" class=\"search-button\">Найти</button>\n"
        "    </form>\n"
        "  </div>\n"
        "</body>\n"
        "</html>";
}


std::string buildResultsPage(const std::vector<std::pair<std::string, int>>& results) {
    std::ostringstream html;
    html << "<!DOCTYPE html>\n"
        << "<html lang=\"ru\">\n"
        << "<head>\n"
        << "  <meta charset=\"utf-8\">\n"
        << "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
        << "  <title>Результаты</title>\n"
        << "</head>\n"
        << "<body>\n"
        << "  <h2>Результаты поиска</h2>\n";

    if (results.empty()) {
        html << "  <p>По вашему запросу ничего не найдено.</p>\n";
    }
    else {
        html << "  <ol>\n";
        for (const auto& r : results) {
            // Экранируем URL для безопасности (опционально)
            html << "    <li><a href=\"" << r.first << "\">" << r.first << "</a> (релевантность: " << r.second << ")</li>\n";
        }
        html << "  </ol>\n";
    }

    html << "  <br><a href=\"/\">← Назад к поиску</a>\n"
        << "</body>\n"
        << "</html>";
    return html.str();
}

std::string buildErrorPage(const std::string& message) {
    return
        "<!DOCTYPE html>\n"
        "<html lang=\"ru\">\n"
        "<head>\n"
        "  <meta charset=\"utf-8\">\n"
        "  <meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n"
        "  <title>Ошибка</title>\n"
        "</head>\n"
        "<body>\n"
        "  <h2>Ошибка сервера</h2>\n"
        "  <p>" + message + "</p>\n"
        "  <br><a href=\"/\">← Назад к поиску</a>\n"
        "</body>\n"
        "</html>";
}

