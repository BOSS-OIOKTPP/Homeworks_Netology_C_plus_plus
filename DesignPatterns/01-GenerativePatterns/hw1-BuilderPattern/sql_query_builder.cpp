#include "sql_query_builder.h"
#include <sstream>
#include <algorithm>

SqlSelectQueryBuilder::SqlSelectQueryBuilder(): pvAllColumns(false) {}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(const std::string& column) {
    if (!column.empty()) {
        pvColumns.push_back(column);
    }
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(const std::string& table) {
    if (!table.empty()) {
        pvTable = table;
    }
    return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::string& column, const std::string& value) {
    if (!column.empty() && !value.empty()) {
        pvWhereConditions[column] = value;
    }
    return *this;
}

std::string SqlSelectQueryBuilder::BuildQuery() const {
    std::ostringstream query;

    // SELECT часть
    query << "SELECT ";
    if (pvColumns.empty() || pvAllColumns) {
        query << "*";
    }
    else {
        for (size_t i = 0; i < columns_.size(); ++i) {
            query << columns_[i];
            if (i != columns_.size() - 1) {
                query << ", ";
            }
        }
    }

    // FROM часть
    if (!table_.empty()) {
        query << " FROM " << table_;
    }
    else {
        // Можно бросить исключение или вернуть пустую строку
        return "";
    }

    // WHERE часть
    if (!where_conditions_.empty()) {
        query << " WHERE ";
        auto it = where_conditions_.begin();
        size_t count = 0;

        while (it != where_conditions_.end()) {
            query << it->first << "=" << it->second;
            ++it;
            if (it != where_conditions_.end()) {
                query << " AND ";
            }
        }
    }

    query << ";";
    return query.str();
}

void SqlSelectQueryBuilder::Reset() {
    pvColumns.clear();
    pvTable.clear();
    pvWhereConditions.clear();
    pvAllColumns = false;
}