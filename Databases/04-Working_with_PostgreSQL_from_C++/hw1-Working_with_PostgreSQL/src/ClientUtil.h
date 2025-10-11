#pragma once

#include <pqxx/pqxx>
#include <string>
#include <vector>


struct Client {
    int client_id;
    std::string first_name;
    std::string last_name;
    std::string email;
    std::vector<std::string> phones;
};

class ClientUtil {
private:
    std::string fconnection_string;
    std::unique_ptr<pqxx::connection> fconnection;
public:
    ClientUtil(const std::string& connection_string);

    // Создание соединения с БД
    bool Сonnect(std::string& err);

    // Проверка соединения с БД
    bool isConnected() const;

    // Закрываем соединение
    void Disconnect();

    

    // Создаем таблицы
    bool CreateTables(std::string& err);

    // Добавляем клиента
    bool AddClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::vector<std::string>& phone_number, int& out_client_id, std::string& err);

    // Изменяем клиента
    bool UpdateClient(int client_id, const std::string& first_name, const std::string& last_name, 
        const std::string& email, std::string& err);

    // Удаляем клиента
    bool DeleteClient(int client_id, std::string& err);

    // Добавляем телефон
    bool AddPhoneNumber(int client_id, const std::string& phone_number, std::string& err);

    // Удаляем телефон
    bool DeletePhoneNumber(int client_id, const std::string& phone_number, std::string& err);

    // Поиск клиента
    bool FindClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::string& phone_number, int& client_id, std::string& err);



    // Информация о базе данных
    std::string GetDatabaseInfo() const;
};

