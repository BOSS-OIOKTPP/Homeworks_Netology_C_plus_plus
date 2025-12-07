#pragma once

#include <string>
#include <vector>
#include <map>

class SqlSelectQueryBuilder {
public:
    // добавить столбец в список выбора
    SqlSelectQueryBuilder& AddColumn(const std::string& column);
    // добавить таблицу
    SqlSelectQueryBuilder& AddFrom(const std::string& table);
    // добавить условие
    SqlSelectQueryBuilder& AddWhere(const std::string& column, const std::string& value);
    // добавить условие
    SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;

    // Формируем запрос
    std::string BuildQuery() const;

    // Сбрасываем состояние для повторного использования
    void Reset();

private:
    // Список столбцов
    std::vector<std::string> pvColumns;
    // Наименование таблицы
    std::string pvTable;   
    // Условия отбора
    std::map<std::string, std::string> pvWhere;    
};

