#include "ClientUtil.h"
#include <sstream>


// Конструктор
ClientUtil::ClientUtil(const std::string& connection_string): fconnection_string(connection_string) {}


// Создание соединения с БД
void ClientUtil::Сonnect() {
    // Если соединение установлено, то выходим
    if (isConnected()) return ;    
    // Подключаемся к базе данных    
    fconnection = std::make_unique<pqxx::connection>(fconnection_string);
}

// Проверка соединения с БД
bool ClientUtil::isConnected() const {
    return fconnection != nullptr;
}

// Закрываем соединение с БД
void ClientUtil::Disconnect() {
    if (isConnected())
        fconnection.reset();
}


// Создаем таблицы
void ClientUtil::CreateTables() {
    pqxx::work tx(*fconnection);

    tx.exec(
        "CREATE TABLE IF NOT EXISTS client ("
        "client_id SERIAL PRIMARY KEY,"
        "first_name VARCHAR(50) NOT NULL,"
        "last_name VARCHAR(50) NOT NULL,"
        "email VARCHAR(100) UNIQUE NOT NULL)"
    );

    tx.exec(
        "CREATE TABLE IF NOT EXISTS phone_number ("
        "phone_number_id SERIAL PRIMARY KEY,"
        "client_id INTEGER REFERENCES client(client_id) ON DELETE CASCADE,"
        "number VARCHAR(20) NOT NULL)"
    );

    tx.commit();            
}

// Добавляем клиента
int ClientUtil::AddClient(const std::string& first_name, const std::string& last_name,
    const std::string& email, const std::vector<std::string>& phone_number) {

    pqxx::work tx(*fconnection);

    // Добавляем клиента и возвращаем идентификатор
    pqxx::result result = tx.exec_params(
        "INSERT INTO client (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING client_id",
        first_name, last_name, email
    );

    int out_client_id = result[0][0].as<int>();

    // Добавляем номера телефонов, если они есть
    for (const auto& number : phone_number) {
        if (!number.empty()) {  // Проверяем, что телефон не пустой
            tx.exec_params(
                "INSERT INTO phone_number (client_id, number) VALUES ($1, $2)",
                out_client_id, number
            );
        }
    }

    tx.commit();        
    return out_client_id;
};

// Изменяем клиента
void ClientUtil::UpdateClient(int client_id, const std::string& first_name, const std::string& last_name, const std::string& email) {

    pqxx::work tx(*fconnection);

    std::string query = "UPDATE client SET ";
    std::vector<std::string> updates;
    std::vector<std::string> params;

    // Указали какие поля обновляем
    if (!first_name.empty()) {
        updates.push_back("first_name = $" + std::to_string(updates.size() + 1));
        params.push_back(first_name);
    }
    if (!last_name.empty()) {
        updates.push_back("last_name = $" + std::to_string(updates.size() + 1));
        params.push_back(last_name);
    }
    if (!email.empty()) {
        updates.push_back("email = $" + std::to_string(updates.size() + 1));
        params.push_back(email);
    }

    // Если нет данных для обновления, то выходим
    if (updates.empty()) {
        //err = "Нет данных для обновления";
        return ;
    }        

    // Собрали запрос
    query += pqxx::separated_list(", ", updates.begin(), updates.end());
    query += " WHERE client_id = $" + std::to_string(params.size() + 1);
        
    // Добавляем значение для последнего параметра
    params.push_back(std::to_string(client_id));

    // Выполняем запрос
    tx.exec_params(query, pqxx::prepare::make_dynamic_params(params));

    tx.commit();        
}

// Удаляем клиента
void ClientUtil::DeleteClient(int client_id) {
    
    pqxx::work tx(*fconnection);

    // Проверяем, существует ли клиент
    pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id);

    if (client_check.empty()) {        
        throw std::runtime_error("Клиент с идентификатором " + std::to_string(client_id) + " не найден.");
    }

    tx.exec_params("DELETE FROM client WHERE client_id = $1", client_id);

    tx.commit();  
}

// Поиск клиента
std::vector<Client> ClientUtil::FindClient(const int client_id, const std::string& first_name, const std::string& last_name,
    const std::string& email, const std::string& phone_number) {

    std::vector<Client> clients;

    {
        pqxx::work tx(*fconnection);

        std::string query =
            "SELECT DISTINCT c.client_id, c.first_name, c.last_name, c.email "
            "FROM client c "
            "LEFT JOIN phone_number pn ON c.client_id = pn.client_id ";

        std::vector<std::string> condition;     // список условий
        std::vector<std::string> params;        // список значений
        int int_param = 0;
        bool has_int_param = false;

        // Составляем условие поиска
        if (client_id != 0) {
            condition.push_back("c.client_id = $" + std::to_string(condition.size() + 1));
            int_param = client_id;
            has_int_param = true;
        }
        if (client_id != 0) {
            condition.push_back("c.client_id = $" + std::to_string(condition.size() + 1));
            params.push_back(std::to_string(client_id));
        }
        if (!first_name.empty()) {
            condition.push_back("c.first_name ILIKE $" + std::to_string(condition.size() + 1));
            params.push_back(first_name);
        }
        if (!last_name.empty()) {
            condition.push_back("c.last_name ILIKE $" + std::to_string(condition.size() + 1));
            params.push_back(last_name);
        }
        if (!email.empty()) {
            condition.push_back("c.email ILIKE $" + std::to_string(condition.size() + 1));
            params.push_back(email);
        }
        if (!phone_number.empty()) {
            condition.push_back("pn.number ILIKE $" + std::to_string(condition.size() + 1));
            params.push_back(phone_number);
        }

        // Если нет данных для поиска - выходим
        if (condition.empty()) {
            return clients;
        }

        // Собираем запрос        
        query += " WHERE (" + pqxx::separated_list(" AND ", condition.begin(), condition.end()) + ") ";

        // Выполняем запрос
        pqxx::result res;
        if (has_int_param) {
            // Если есть client_id, передаем его как число
            res = tx.exec_params(query, int_param, pqxx::prepare::make_dynamic_params(params));
        }
        else {
            // Если нет client_id, только строковые параметры
            res = tx.exec_params(query, pqxx::prepare::make_dynamic_params(params));
        }

        // Запоминаем клиентов
        for (const auto& row : res) {
            Client client;
            client.client_id = row[0].as<int>();
            client.first_name = row[1].as<std::string>();
            client.last_name = row[2].as<std::string>();
            client.email = row[3].as<std::string>();            
            clients.push_back(client);
        }
    }

    // Ищим телефоны
    for (auto& client : clients) 
        client.phones = GetClientPhones(client.client_id);      
    

    return clients;            
}

// Список телефонных номеров клиента
std::vector<std::string> ClientUtil::GetClientPhones(int client_id) {
    
    std::vector<std::string> phones;
    
    pqxx::work txn(*fconnection);

    pqxx::result res = txn.exec_params(
        "SELECT number FROM phone_number WHERE client_id = $1 ",
        client_id
    );

    for (const auto& row : res) {
        phones.push_back(row[0].as<std::string>());
    }

    return phones;
}

// Информация о базе данных
std::string ClientUtil::GetDatabaseInfo() const {
    std::stringstream info;

    if (!isConnected()) {
        info << "Не выполнено подключение к базе данных";        
    }
    else {
        info << "Database: " << fconnection->dbname() << "\n";
        info << "Username: " << fconnection->username() << "\n";
        info << "Host: " << fconnection->hostname() << "\n";
        info << "Port: " << fconnection->port() << "\n";
        info << "Server Version: " << fconnection->server_version() << "\n";
    }

    return info.str();
}

// Добавляем телефон
void ClientUtil::AddPhoneNumber(int client_id, const std::string& phone_number) {
    pqxx::work tx(*fconnection);

    // Проверяем, существует ли клиент
    pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id );

    std::string err{};
    if (client_check.empty())    
        throw std::runtime_error("Клиент с идентификатором " + std::to_string(client_id) + " не найден.");

    // Проверяем, существует ли такой номер телефона у этого клиента
    pqxx::result phone_number_check = tx.exec_params(
        "SELECT client_id FROM phone_number WHERE client_id = $1 AND number = $2",
        client_id, phone_number
    );

    if (!phone_number_check.empty()) 
        throw std::runtime_error("ОШИБКА. Телефонный номер '" + phone_number + "' уже существует у клиента с идентификатором " + std::to_string(client_id) + ".");

    // Добавляем телефон
    tx.exec_params(
        "INSERT INTO phone_number (client_id, number) VALUES ($1, $2)",
        client_id, phone_number
    );

    tx.commit();            
}

// Удаляем телефон
void ClientUtil::DeletePhoneNumber(int client_id, const std::string& phone_number) {
    
    pqxx::work tx(*fconnection);

    // Проверяем, существует ли клиент
    pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id);

    if (client_check.empty()) 
        throw std::runtime_error("Клиент с идентификатором " + std::to_string(client_id) + " не найден.");

    // Удаляем телефон
    pqxx::result result = tx.exec_params(
        "DELETE FROM phone_number WHERE client_id = $1 AND number = $2",
        client_id, phone_number
    );

    tx.commit();

    // Если вернулось количество, то запись была найдена и удалена
    if (result.affected_rows() != 0)                 
        throw std::runtime_error("Телефон не найден.");
      
}