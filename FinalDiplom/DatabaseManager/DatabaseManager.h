#pragma once

#include <pqxx/pqxx>
#include <string>

class DatabaseManager
{
public:
    // Конструктор: сохраняем строку подключения, но не соединяемся сразу. 
    // explicit используем, чтобы не было неявного преобразования
    explicit DatabaseManager(const std::string& connection_string);

    // Создаем соединения с БД
    void Connect();
    // Проверяем соединение с БД
    bool IsConnected() const;
    // Закрываем соединение
    void Disconnect();

    // Создаем таблицы
    void CreateTables();

    // Информация о базе данных
    std::string GetDatabaseInfo() const;

    // Сохраняем документ и частоту слов в БД
    void SaveDocument(const std::string& url, const std::unordered_map<std::string, int>& word_freq);

private:
    std::string _connection_string;
    std::unique_ptr<pqxx::connection> _connection;
};

