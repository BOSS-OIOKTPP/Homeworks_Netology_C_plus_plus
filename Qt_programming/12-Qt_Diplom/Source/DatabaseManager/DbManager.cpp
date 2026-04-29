#include "DbManager.h"

#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>

DbManager::DbManager(QString configPath)
    : m_configPath(std::move(configPath))
{
}

DbManager::~DbManager()
{
    if (m_db.isValid() && m_db.isOpen()) {
        m_db.close();
    }

    if (QSqlDatabase::contains(m_connectionName)) {
        m_db = QSqlDatabase();
        QSqlDatabase::removeDatabase(m_connectionName);
    }
}

bool DbManager::connectToDatabase(QString *errorMessage)
{
    if (!loadConfig(errorMessage)) {
        return false;
    }

    if (QSqlDatabase::contains(m_connectionName)) {
        m_db = QSqlDatabase::database(m_connectionName);
    } else {
        m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), m_connectionName);
    }

    m_db.setHostName(m_host);
    m_db.setPort(m_port);
    m_db.setDatabaseName(m_dbName);
    m_db.setUserName(m_user);
    m_db.setPassword(m_password);
    m_db.setConnectOptions(QStringLiteral("client_encoding=UTF8"));

    if (!m_db.open()) {
        if (tryCreateDatabaseIfMissing(errorMessage)) {
            if (m_db.open()) {
                QSqlQuery setupQuery(m_db);
                setupQuery.exec(QStringLiteral("SET client_min_messages TO warning;"));
                return true;
            }
        }

        if (errorMessage != nullptr) {
            *errorMessage = m_db.lastError().text();
        }
        return false;
    }

    QSqlQuery setupQuery(m_db);
    setupQuery.exec(QStringLiteral("SET client_min_messages TO warning;"));

    return true;
}

bool DbManager::createTables(bool *tablesAlreadyExist, QString *errorMessage)
{
    if (!isOpen()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Соединение с базой данных не открыто.");
        }
        return false;
    }

    bool allTablesExist = false;
    if (!areAllTablesExist(&allTablesExist, errorMessage)) {
        return false;
    }
    if (tablesAlreadyExist != nullptr) {
        *tablesAlreadyExist = allTablesExist;
    }
    if (allTablesExist) {
        return true;
    }

    QSqlQuery query(m_db);

    const QStringList statements = {
        QStringLiteral(
            "CREATE TABLE IF NOT EXISTS documents ("
            "id SERIAL PRIMARY KEY, "
            "path TEXT NOT NULL UNIQUE, "
            "indexed_at TIMESTAMP NOT NULL DEFAULT NOW()"
            ");"),
        QStringLiteral(
            "CREATE TABLE IF NOT EXISTS words ("
            "id SERIAL PRIMARY KEY, "
            "word TEXT NOT NULL UNIQUE"
            ");"),
        QStringLiteral(
            "CREATE TABLE IF NOT EXISTS document_words ("
            "document_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE, "
            "word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE, "
            "frequency INTEGER NOT NULL CHECK (frequency >= 0), "
            "PRIMARY KEY (document_id, word_id)"
            ");")
    };

    for (const QString &sql : statements) {
        if (!query.exec(sql)) {
            if (errorMessage != nullptr) {
                *errorMessage = query.lastError().text();
            }
            return false;
        }
    }

    return true;
}

bool DbManager::isOpen() const
{
    return m_db.isValid() && m_db.isOpen();
}

bool DbManager::saveDocumentWordFrequency(const QString &documentPath,
                                          const QString &word,
                                          int frequency,
                                          QString *errorMessage)
{
    if (!isOpen()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Соединение с базой данных не открыто.");
        }
        return false;
    }

    if (documentPath.trimmed().isEmpty() || word.trimmed().isEmpty() || frequency < 0) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Некорректные параметры записи частоты слова.");
        }
        return false;
    }

    int documentId = 0;
    if (!upsertDocument(documentPath.trimmed(), &documentId, errorMessage)) {
        return false;
    }

    int wordId = 0;
    if (!upsertWord(word.trimmed().toLower(), &wordId, errorMessage)) {
        return false;
    }

    return upsertDocumentWordFrequency(documentId, wordId, frequency, errorMessage);
}

bool DbManager::upsertDocument(const QString &documentPath, int *documentId, QString *errorMessage)
{
    if (documentId == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан указатель documentId.");
        }
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(QStringLiteral(
        "INSERT INTO documents(path) "
        "VALUES(:path) "
        "ON CONFLICT(path) DO UPDATE SET path = EXCLUDED.path "
        "RETURNING id;"));
    query.bindValue(QStringLiteral(":path"), documentPath);

    if (!query.exec() || !query.next()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось сохранить документ '%1': %2")
                                .arg(documentPath, query.lastError().text());
        }
        return false;
    }

    *documentId = query.value(0).toInt();
    return true;
}

bool DbManager::upsertWord(const QString &word, int *wordId, QString *errorMessage)
{
    if (wordId == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан указатель wordId.");
        }
        return false;
    }

    QSqlQuery query(m_db);
    query.prepare(QStringLiteral(
        "INSERT INTO words(word) "
        "VALUES(:word) "
        "ON CONFLICT(word) DO UPDATE SET word = EXCLUDED.word "
        "RETURNING id;"));
    query.bindValue(QStringLiteral(":word"), word);

    if (!query.exec() || !query.next()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось сохранить слово '%1': %2")
                                .arg(word, query.lastError().text());
        }
        return false;
    }

    *wordId = query.value(0).toInt();
    return true;
}

bool DbManager::upsertDocumentWordFrequency(int documentId, int wordId, int frequency, QString *errorMessage)
{
    QSqlQuery query(m_db);
    query.prepare(QStringLiteral(
        "INSERT INTO document_words(document_id, word_id, frequency) "
        "VALUES(:document_id, :word_id, :frequency) "
        "ON CONFLICT(document_id, word_id) "
        "DO UPDATE SET frequency = EXCLUDED.frequency;"));
    query.bindValue(QStringLiteral(":document_id"), documentId);
    query.bindValue(QStringLiteral(":word_id"), wordId);
    query.bindValue(QStringLiteral(":frequency"), frequency);

    if (!query.exec()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось сохранить частоту слова в документе: %1")
                                .arg(query.lastError().text());
        }
        return false;
    }

    return true;
}

bool DbManager::loadConfig(QString *errorMessage)
{
    QSettings settings(m_configPath, QSettings::IniFormat);

    if (!settings.childGroups().contains(QStringLiteral("Database"))) {
        if (errorMessage != nullptr) {
            *errorMessage =
                QStringLiteral("В файле конфигурации отсутствует секция [Database]: %1").arg(m_configPath);
        }
        return false;
    }

    m_host = settings.value(QStringLiteral("Database/Host")).toString().trimmed();
    m_port = settings.value(QStringLiteral("Database/Port"), 5432).toInt();
    m_dbName = settings.value(QStringLiteral("Database/Name")).toString().trimmed();
    m_user = settings.value(QStringLiteral("Database/User")).toString().trimmed();
    m_password = settings.value(QStringLiteral("Database/Password")).toString();

    if (m_host.isEmpty() || m_dbName.isEmpty() || m_user.isEmpty()) {
        if (errorMessage != nullptr) {
            *errorMessage =
                QStringLiteral("Параметры подключения к БД заполнены не полностью в файле: %1").arg(m_configPath);
        }
        return false;
    }

    return true;
}

bool DbManager::areAllTablesExist(bool *allExist, QString *errorMessage)
{
    if (allExist == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не передан указатель результата проверки таблиц.");
        }
        return false;
    }

    QSqlQuery query(m_db);
    const QString sql = QStringLiteral(
        "SELECT COUNT(*) "
        "FROM information_schema.tables "
        "WHERE table_schema = 'public' "
        "  AND table_name IN ('documents', 'words', 'document_words');");

    if (!query.exec(sql)) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось проверить существование таблиц: %1")
                                .arg(query.lastError().text());
        }
        return false;
    }

    if (!query.next()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось получить результат проверки существования таблиц.");
        }
        return false;
    }

    const int existingTablesCount = query.value(0).toInt();
    *allExist = (existingTablesCount == 3);
    return true;
}

bool DbManager::tryCreateDatabaseIfMissing(QString *errorMessage)
{
    const QString dbErrorText = m_db.lastError().text();
    const QString dbErrorTextLower = dbErrorText.toLower();

    const bool dbMissing = dbErrorTextLower.contains(QStringLiteral("does not exist"))
                           || dbErrorTextLower.contains(QStringLiteral("не существует"));

    if (!dbMissing) {
        return false;
    }

    return createDatabase(errorMessage);
}

bool DbManager::createDatabase(QString *errorMessage)
{
    const QString adminConnectionName = QStringLiteral("dbmanager_admin_connection");

    if (QSqlDatabase::contains(adminConnectionName)) {
        QSqlDatabase::removeDatabase(adminConnectionName);
    }

    QSqlDatabase adminDb = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), adminConnectionName);
    adminDb.setHostName(m_host);
    adminDb.setPort(m_port);
    adminDb.setDatabaseName(QStringLiteral("postgres"));
    adminDb.setUserName(m_user);
    adminDb.setPassword(m_password);

    if (!adminDb.open()) {
        if (errorMessage != nullptr) {
            *errorMessage =
                QStringLiteral("Не удалось подключиться к служебной БД postgres для создания новой БД: %1")
                    .arg(adminDb.lastError().text());
        }
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return false;
    }

    QString escapedDbName = m_dbName;
    escapedDbName.replace(QStringLiteral("\""), QStringLiteral("\"\""));

    QSqlQuery query(adminDb);
    const QString createDbSql = QStringLiteral("CREATE DATABASE \"%1\";").arg(escapedDbName);
    if (!query.exec(createDbSql)) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось создать базу данных %1: %2")
                                .arg(m_dbName, query.lastError().text());
        }
        adminDb.close();
        adminDb = QSqlDatabase();
        QSqlDatabase::removeDatabase(adminConnectionName);
        return false;
    }

    adminDb.close();
    adminDb = QSqlDatabase();
    QSqlDatabase::removeDatabase(adminConnectionName);
    return true;
}
