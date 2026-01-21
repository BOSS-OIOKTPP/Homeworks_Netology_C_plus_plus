#include "DatabaseManager.h"

// Конструктор
DatabaseManager::DatabaseManager(const std::string& connection_string) : _connection_string(connection_string) {}

// Создание соединения с БД
void DatabaseManager::Connect() {
    // Если соединение установлено, то выходим
    if (IsConnected()) return;
    // Подключаемся к базе данных    
    try {
        _connection = std::make_unique<pqxx::connection>(_connection_string);        
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Ошибка подключения к базе данных: " + std::string(e.what()));
    }
}

// Проверяем соединение с БД
bool DatabaseManager::IsConnected() const {
    return _connection != nullptr && _connection->is_open();
}

// Закрываем соединение с БД
void DatabaseManager::Disconnect() {
    _connection.reset();
}

// Создаем таблицы
void DatabaseManager::CreateTables() {
    //if (!IsConnected()) 
    //    throw std::logic_error("Не удалось создать таблицы: нет соединения с базой данных");
    
    pqxx::work tx(*_connection);

    // Таблица документов
    tx.exec(R"(
        CREATE TABLE IF NOT EXISTS documents (
            id SERIAL PRIMARY KEY,
            url TEXT NOT NULL UNIQUE
        );
    )");

    // Таблица слов
    tx.exec(R"(
        CREATE TABLE IF NOT EXISTS words (
            id SERIAL PRIMARY KEY,
            word TEXT NOT NULL UNIQUE
        );
    )");

    // Связь многие-ко-многим + частота
    tx.exec(R"(
        CREATE TABLE IF NOT EXISTS doc_word (
            doc_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE,
            word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,
            freq INTEGER NOT NULL CHECK (freq > 0),
            PRIMARY KEY (doc_id, word_id)
        );
    )");

    tx.commit();
}

// Информация о базе данных
std::string DatabaseManager::GetDatabaseInfo() const {
    std::stringstream info;

    if (!IsConnected()) {
        info << "Не выполнено подключение к базе данных";
    }
    else {
        info << "Database: " << _connection->dbname() << "\n";
        info << "Username: " << _connection->username() << "\n";
        info << "Host: " << _connection->hostname() << "\n";
        info << "Port: " << _connection->port() << "\n";
        info << "Server Version: " << _connection->server_version() << "\n";
    }

    return info.str();
}

// Сохраняем документ и частоту слов в БД
void DatabaseManager::SaveDocument(const std::string& url, const std::unordered_map<std::string, int>& word_freq)
{
    //if (!IsConnected()) 
    //    throw std::logic_error("Нет подключения к базе данных");
    

    pqxx::work tx(*_connection);

    // 1. Вставляем документ (игнорируем дубликаты)
    pqxx::result doc_result = tx.exec_params(
        "INSERT INTO documents (url) VALUES ($1) "
        "ON CONFLICT (url) DO NOTHING RETURNING id",
        url
    );

    int doc_id;
    if (!doc_result.empty()) {
        doc_id = doc_result[0][0].as<int>();
    }
    else {
        // Документ уже существует — получаем его ID
        pqxx::result existing = tx.exec_params(
            "SELECT id FROM documents WHERE url = $1",
            url
        );
        if (existing.empty()) {
            throw std::runtime_error("Не удалось получить ID документа");
        }
        doc_id = existing[0][0].as<int>();
    }

    // 2. Обрабатываем каждое слово
    for (const auto& [word, freq] : word_freq) {
        if (freq <= 0) continue; // Защита от некорректных данных

        // Вставляем слово (игнорируем дубликаты)
        pqxx::result word_result = tx.exec_params(
            "INSERT INTO words (word) VALUES ($1) "
            "ON CONFLICT (word) DO NOTHING RETURNING id",
            word
        );

        int word_id;
        if (!word_result.empty()) {
            word_id = word_result[0][0].as<int>();
        }
        else {
            // Слово уже существует — получаем его ID
            pqxx::result existing = tx.exec_params(
                "SELECT id FROM words WHERE word = $1",
                word
            );
            if (existing.empty()) {
                throw std::runtime_error("Не удалось получить ID слова");
            }
            word_id = existing[0][0].as<int>();
        }

        // 3. Сохраняем связь с частотой
        tx.exec_params(
            "INSERT INTO doc_word (doc_id, word_id, freq) VALUES ($1, $2, $3) "
            "ON CONFLICT (doc_id, word_id) DO UPDATE SET freq = $3",
            doc_id, word_id, freq
        );
    }

    tx.commit();
    //std::cout << "✅ Сохранено " << word_freq.size() << " слов для: " << url << "\n";
}
