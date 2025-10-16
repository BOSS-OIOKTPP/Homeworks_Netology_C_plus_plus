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

    // для вывода
    std::string toString() const {
        std::stringstream ss;
        ss << "Идентификатор: " << client_id
           << ", Имя: " << first_name << " " << last_name
           << ", Email: " << email
           << ", Телефоны: ";

        if (phones.empty()) {
            ss << "нет";
        }
        else {
            for (size_t i = 0; i < phones.size(); ++i) {
                if (i > 0) ss << ", ";
                ss << phones[i];
            }
        }

        return ss.str();
    }
};

class ClientUtil {
private:
    std::string fconnection_string;
    std::unique_ptr<pqxx::connection> fconnection;
public:
    ClientUtil(const std::string& connection_string);

    // Создание соединения с БД
    void Сonnect();

    // Проверка соединения с БД
    bool isConnected() const;

    // Закрываем соединение
    void Disconnect();

    

    // Создаем таблицы
    void CreateTables();

    // Добавляем клиента
    int AddClient(const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::vector<std::string>& phone_number);

    // Изменяем клиента
    void UpdateClient(int client_id, const std::string& first_name, const std::string& last_name, const std::string& email);

    // Удаляем клиента
    void DeleteClient(int client_id);

    // Добавляем телефон
    void AddPhoneNumber(int client_id, const std::string& phone_number);

    // Удаляем телефон
    void DeletePhoneNumber(int client_id, const std::string& phone_number);

    // Поиск клиента
    std::vector<Client> FindClient(const int client_id, const std::string& first_name, const std::string& last_name,
        const std::string& email, const std::string& phone_number);

    // Поиск телефонов
    std::vector<std::string> GetClientPhones(int client_id);

    // Информация о базе данных
    std::string GetDatabaseInfo() const;
};

