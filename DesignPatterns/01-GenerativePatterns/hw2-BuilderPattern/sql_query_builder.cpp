#include "sql_query_builder.h"
#include <sstream>

// добавить столбец в список выбора
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) {
    if (!column.empty()) {
        pvColumns.push_back(column);
    }
    return *this;
}

// добавить таблицу
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
    if (!table.empty()) {
        pvTable = table;
    }
    return *this;
}

// добавить условие
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column, const std::string& value) {
    if (!column.empty() && !value.empty()) {
        pvWhere[column] = value;
    }
    return *this;
}
// добавить условие
SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept {
    for (const auto& pair : kv) {
        if (!pair.first.empty() && !pair.second.empty()) {
            pvWhere[pair.first] = pair.second;
        }
    }
    return *this;
};

// Формируем запрос
std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::ostringstream query;

    // SELECT часть
    query << "SELECT ";
    if (pvColumns.empty()) {
        query << "*";
    }
    else {
        for (size_t i = 0; i < pvColumns.size(); ++i) {
            query << pvColumns[i];
            if (i != pvColumns.size() - 1) {
                query << ", ";
            }
        }
    }

    // FROM часть
    if (!pvTable.empty()) {
        query << " FROM " << pvTable;
    }
    else {        
        return "";
    }

    // WHERE часть
    if (!pvWhere.empty()) {
        query << " WHERE ";
        auto it = pvWhere.begin();
        size_t count = 0;

        while (it != pvWhere.end()) {
            query << it->first << "=" << it->second;
            ++it;
            if (it != pvWhere.end()) {
                query << " AND ";
            }
        }
    }

    query << ";";
    return query.str();
}

// Сбрасываем состояние для повторного использования
void SqlSelectQueryBuilder::Reset() {
    pvColumns.clear();
    pvTable.clear();
    pvWhere.clear();    
}