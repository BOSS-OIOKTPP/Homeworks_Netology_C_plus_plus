#include <iostream>
#include "SpiderEngine.h"
#include "LinkExtractor.h"

// Конструктор
SpiderEngine::SpiderEngine(const std::string& start_url, int max_depth, DatabaseManager& db)
    : _start_url(start_url), _max_depth(max_depth), _db(db) {}

// Запускаем обход
void SpiderEngine::Run() {
    std::cout << "Запуск паука. Стартовая страница: " << _start_url << ", Макс. глубина: " << _max_depth << "\n";
    Crawl(_start_url, 1);
    std::cout << "Обход завершён. Обработано страниц: " << _visited.size() << "\n";
}

void SpiderEngine::Crawl(const std::string& url, int depth) {
    // Проверка глубины
    if (depth > _max_depth) 
        return;    

    // Проверка посещения
    if (_visited.count(url)) 
        return;
    
    _visited.insert(url);

    std::cout << "[Уровень " << depth << "] Обработка: " << url << "\n";

    try {
        // 1. Скачиваем страницу
        std::string html = _client.fetch(url);

        // 2. Индексируем текст
        auto wordFreq = _indexer.ProcessHtml(html);

        // 3. Сохраняем в БД 
        if (!wordFreq.empty()) 
            _db.SaveDocument(url, wordFreq);        

        // 4. Если не последняя глубина — ищем ссылки
        if (depth < _max_depth) {
            auto links = LinkExtractor::Extract(html, url);
            for (const auto& link : links) 
                Crawl(link, depth + 1);            
        }
    }
    catch (const pqxx::sql_error& e) {
        std::cerr << "Ошибка БД при обработке " << url << ": " << e.what() << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Ошибка при обработке " << url << ": " << e.what() << "\n";
    }
}