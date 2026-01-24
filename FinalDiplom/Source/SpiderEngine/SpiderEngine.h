#pragma once
#include <string>
#include <unordered_set>
#include "SpiderClient.h"
#include "Indexer.h"
#include "DatabaseManager.h"

// Рекурсивный обход веб-страниц
class SpiderEngine {
public:
    // Конструктор
    SpiderEngine(const std::string& start_url, int max_depth, DatabaseManager& db);

    // Запускаем обход
    void Run();
private:
    // Рекурсивный обход ссылок
    void Crawl(const std::string& url, int current_depth);

    std::string _start_url;
    int _max_depth;
    DatabaseManager& _db;
    std::unordered_set<std::string> _visited; // избегаем повторного обхода
    SpiderClient _client;
    Indexer _indexer;
};
