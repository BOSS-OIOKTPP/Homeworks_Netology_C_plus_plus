#include "DatabaseManager.h"

// Конструктор
DatabaseManager::DatabaseManager(const std::string& connection_string) : _connection_string(connection_string) {}

// Создание соединения с БД
void DatabaseManager::Сonnect() {
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
    //if (!IsConnected()) {
    //    throw std::logic_error("Не удалось создать таблицы: нет соединения с базой данных");
    //}    

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
