#pragma once

#include <QString>
#include <QSqlDatabase>

struct DbConfig
{
    QString host;
    int port = 5432;
    QString databaseName;
    QString user;
    QString password;

    QString adminDatabase = "postgres";
    QString adminUser;
    QString adminPassword;
};

class DatabaseManager
{
public:
    explicit DatabaseManager(DbConfig config);
    ~DatabaseManager();

    bool ensureDatabaseAndConnect(QString* errorMessage = nullptr);
    bool ensureSchema(QString* errorMessage = nullptr) const;

private:
    bool openTargetConnection(QString* errorMessage = nullptr);
    bool createDatabaseIfMissing(QString* errorMessage = nullptr) const;

private:
    DbConfig m_config;
    QString m_connectionName;
    QSqlDatabase m_db;
};
