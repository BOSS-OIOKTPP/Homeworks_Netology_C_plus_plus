#include "DatabaseManager.h"

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QUuid>
#include <utility>

namespace
{
QString buildPgConnectionOptions(const QString& appName)
{
    return "connect_timeout=5 application_name=" + appName;
}
}

DatabaseManager::DatabaseManager(DbConfig config)
    : m_config(std::move(config))
    , m_connectionName("db_main_" + QUuid::createUuid().toString(QUuid::WithoutBraces))
{
}

DatabaseManager::~DatabaseManager()
{
    if (m_db.isValid()) {
        if (m_db.isOpen()) {
            m_db.close();
        }
        m_db = QSqlDatabase();
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

bool DatabaseManager::ensureDatabaseAndConnect(QString* errorMessage)
{
    if (openTargetConnection(errorMessage)) {
        return true;
    }

    return createDatabaseIfMissing(errorMessage) && openTargetConnection(errorMessage);
}

bool DatabaseManager::ensureSchema(QString* errorMessage) const
{
    if (!m_db.isValid() || !m_db.isOpen()) {
        if (errorMessage != nullptr) {
            *errorMessage = "Нет активного подключения к БД.";
        }
        return false;
    }

    QSqlQuery query(m_db);
    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS documents ("
            "id SERIAL PRIMARY KEY, "
            "file_path TEXT NOT NULL UNIQUE, "
            "indexed_at TIMESTAMP NOT NULL DEFAULT CURRENT_TIMESTAMP"
            ");")) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS words ("
            "id SERIAL PRIMARY KEY, "
            "word TEXT NOT NULL UNIQUE"
            ");")) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    if (!query.exec(
            "CREATE TABLE IF NOT EXISTS doc_word ("
            "doc_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE, "
            "word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE, "
            "freq INTEGER NOT NULL CHECK(freq > 0), "
            "PRIMARY KEY(doc_id, word_id)"
            ");")) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        return false;
    }

    return true;
}

bool DatabaseManager::openTargetConnection(QString* errorMessage)
{
    if (!m_db.isValid()) {
        m_db = QSqlDatabase::addDatabase("QPSQL", m_connectionName);
    }

    m_db.setHostName(m_config.host);
    m_db.setPort(m_config.port);
    m_db.setDatabaseName(m_config.databaseName);
    m_db.setUserName(m_config.user);
    m_db.setPassword(m_config.password);
    m_db.setConnectOptions(buildPgConnectionOptions("qt_indexer_main"));

    if (m_db.open()) {
        return true;
    }

    if (errorMessage != nullptr) {
        *errorMessage = m_db.lastError().text();
    }
    return false;
}

bool DatabaseManager::createDatabaseIfMissing(QString* errorMessage) const
{
    const QString adminConnectionName =
        "db_admin_" + QUuid::createUuid().toString(QUuid::WithoutBraces);
    QSqlDatabase adminDb = QSqlDatabase::addDatabase("QPSQL", adminConnectionName);

    adminDb.setHostName(m_config.host);
    adminDb.setPort(m_config.port);
    adminDb.setDatabaseName(m_config.adminDatabase);
    adminDb.setUserName(m_config.adminUser.isEmpty() ? m_config.user : m_config.adminUser);
    adminDb.setPassword(m_config.adminPassword.isEmpty() ? m_config.password : m_config.adminPassword);
    adminDb.setConnectOptions(buildPgConnectionOptions("qt_indexer_admin"));

    if (!adminDb.open()) {
        if (errorMessage != nullptr) {
            *errorMessage =
                "Не удалось подключиться к служебной БД для создания целевой БД: "
                + adminDb.lastError().text();
        }
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return false;
    }

    QSqlQuery query(adminDb);
    query.prepare("SELECT 1 FROM pg_database WHERE datname = :db_name");
    query.bindValue(":db_name", m_config.databaseName);
    if (!query.exec()) {
        if (errorMessage != nullptr) {
            *errorMessage = query.lastError().text();
        }
        query = QSqlQuery();
        adminDb.close();
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return false;
    }

    if (query.next()) {
        query = QSqlQuery();
        adminDb.close();
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return true;
    }

    const QString escapedDbName = '"' + m_config.databaseName + '"';
    if (!query.exec("CREATE DATABASE " + escapedDbName)) {
        if (errorMessage != nullptr) {
            *errorMessage = "Не удалось создать БД " + m_config.databaseName + ": "
                + query.lastError().text();
        }
        query = QSqlQuery();
        adminDb.close();
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return false;
    }

    query = QSqlQuery();
    adminDb.close();
    adminDb = QSqlDatabase();
    QSqlDatabase::removeDatabase(adminConnectionName);
    return true;
}
