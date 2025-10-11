#include "ClientUtil.h"
#include <sstream>


// Конструктор
ClientUtil::ClientUtil(const std::string& connection_string): fconnection_string(connection_string) {}


// Создание соединения с БД
bool ClientUtil::Сonnect(std::string& err) {
    err = "";

    if (isConnected()) return true;    
    
    try {
        fconnection = std::make_unique<pqxx::connection>(fconnection_string);
        return true;
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;   
    }
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
bool ClientUtil::CreateTables(std::string& err) {
    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;  
    }
    try {        
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
        return true;
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}

// Добавляем клиента
bool ClientUtil::AddClient(const std::string& first_name, const std::string& last_name,
    const std::string& email, const std::vector<std::string>& phone_number, int& out_client_id, std::string& err) {

    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {       
        pqxx::work tx(*fconnection);

        // Добавляем клиента и возвращаем идентификатор
        pqxx::result result = tx.exec_params(
            "INSERT INTO client (first_name, last_name, email) VALUES ($1, $2, $3) RETURNING client_id",
            first_name, last_name, email
        );

        out_client_id = result[0][0].as<int>();

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
        return true;
    }    
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
};

// Изменяем клиента
bool ClientUtil::UpdateClient(int client_id, const std::string& first_name, const std::string& last_name,
    const std::string& email, std::string& err) {

    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {
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
            err = "Нет данных для обновления";
            return false;
        }        

        // Собрали запрос
        query += pqxx::separated_list(", ", updates.begin(), updates.end());
        query += " WHERE client_id = $" + std::to_string(params.size() + 1);
        
        // Добавляем значение для последнего параметра
        params.push_back(std::to_string(client_id));

        // Выполняем запрос
        tx.exec_params(query, pqxx::prepare::make_dynamic_params(params));

        tx.commit();
        return true;
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}

// Удаляем клиента
bool ClientUtil::DeleteClient(int client_id, std::string& err) {
    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {
        pqxx::work tx(*fconnection);

        // Проверяем, существует ли клиент
        pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id);

        if (client_check.empty()) {
            err = "Клиент с идентификатором " + std::to_string(client_id) + " не найден.";
            return false;
        }

        tx.exec_params("DELETE FROM client WHERE client_id = $1", client_id);

        tx.commit();
        return true;
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}

// Поиск клиента
bool ClientUtil::FindClient(const std::string& first_name, const std::string& last_name,
    const std::string& email, const std::string& phone_number, int& client_id, std::string& err) {

    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {
        pqxx::work tx(*fconnection);

        std::string query =
            "SELECT DISTINCT c.client_id "
            "FROM client c "
            "LEFT JOIN phone_number pn ON c.client_id = pn.client_id ";            
            
        std::vector<std::string> condition;     // список условий
        std::vector<std::string> params;        // список значений

        // Составляем условие поиска
        if (!first_name.empty()) {
            condition.push_back("first_name = $" + std::to_string(condition.size() + 1));
            params.push_back(first_name);
        }
        if (!last_name.empty()) {
            condition.push_back("last_name = $" + std::to_string(condition.size() + 1));
            params.push_back(last_name);
        }
        if (!email.empty()) {
            condition.push_back("email = $" + std::to_string(condition.size() + 1));
            params.push_back(email);
        }
        if (!phone_number.empty()) {
            condition.push_back("number = $" + std::to_string(condition.size() + 1));
            params.push_back(phone_number);
        }

        // Если нет данных для поиска - выходим
        if (condition.empty()) {
            err = "Нет данных для поиска";
            return false;
        }

        // Собираем запрос        
        query += " WHERE (" + pqxx::separated_list(" AND ", condition.begin(), condition.end()) + ") LIMIT 1";

        // Выполняем запрос
        pqxx::result res = tx.exec_params(query, pqxx::prepare::make_dynamic_params(params));

        if (!res.empty()) {
            client_id = res[0][0].as<int>();
            return true;
        }
        else {
            err = "";
            return false;
        }        
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
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
bool ClientUtil::AddPhoneNumber(int client_id, const std::string& phone_number, std::string& err) {
    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {
        pqxx::work tx(*fconnection);

        // Проверяем, существует ли клиент
        pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id );

        if (client_check.empty()) {
            err = "Клиент с идентификатором " + std::to_string(client_id) + " не найден.";
            return false;
        }

        // Проверяем, существует ли такой номер телефона у этого клиента
        pqxx::result phone_number_check = tx.exec_params(
            "SELECT client_id FROM phone_number WHERE client_id = $1 AND number = $2",
            client_id, phone_number
        );

        if (!phone_number_check.empty()) {
            err = "ОШИБКА. Телефонный номер '" + phone_number + "' уже существует у клиента с идентификатором " + std::to_string(client_id) + ".";
            return false;
        }

        // Добавляем телефон
        tx.exec_params(
            "INSERT INTO phone_number (client_id, number) VALUES ($1, $2)",
            client_id, phone_number
        );

        tx.commit();        
        return true;
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}

// Удаляем телефон
bool ClientUtil::DeletePhoneNumber(int client_id, const std::string& phone_number, std::string& err) {
    err = "";

    // Проверяем, что соединение создано
    if (!isConnected()) {
        err = "Не выполнено подключение к базе данных";
        return false;
    }

    try {
        pqxx::work tx(*fconnection);

        // Проверяем, существует ли клиент
        pqxx::result client_check = tx.exec_params("SELECT client_id FROM client WHERE client_id = $1", client_id);

        if (client_check.empty()) {
            err = "Клиент с идентификатором " + std::to_string(client_id) + " не найден.";
            return false;
        }

        // Удаляем телефон
        pqxx::result result = tx.exec_params(
            "DELETE FROM phone_number WHERE client_id = $1 AND number = $2",
            client_id, phone_number
        );

        tx.commit();

        // Если вернулось количество, то запись была найдена и удалена
        if (result.affected_rows() > 0)             
            return true;        
        else {
            err = "Телефон не найден.";
            return false;
        }
    }
    catch (const std::exception& e) {
        err = e.what();
        return false;
    }
}