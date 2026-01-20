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
    void Сonnect();
    // Проверяем соединение с БД
    bool IsConnected() const;
    // Закрываем соединение
    void Disconnect();

    // Создаем таблицы
    void CreateTables();

    // Информация о базе данных
    std::string GetDatabaseInfo() const;

private:
    std::string _connection_string;
    std::unique_ptr<pqxx::connection> _connection;
};

