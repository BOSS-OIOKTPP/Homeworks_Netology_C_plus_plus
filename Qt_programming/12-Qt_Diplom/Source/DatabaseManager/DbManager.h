#pragma once

#include <QSqlDatabase>
#include <QString>

class DbManager
{
public:
    explicit DbManager(QString configPath = QStringLiteral("config.ini"));
    ~DbManager();

    bool connectToDatabase(QString *errorMessage = nullptr);
    bool createTables(bool *tablesAlreadyExist = nullptr, QString *errorMessage = nullptr);
    bool saveDocumentWordFrequency(const QString &documentPath,
                                   const QString &word,
                                   int frequency,
                                   QString *errorMessage = nullptr);
    bool isOpen() const;

private:
    bool upsertDocument(const QString &documentPath, int *documentId, QString *errorMessage = nullptr);
    bool upsertWord(const QString &word, int *wordId, QString *errorMessage = nullptr);
    bool upsertDocumentWordFrequency(int documentId, int wordId, int frequency, QString *errorMessage = nullptr);

    bool loadConfig(QString *errorMessage = nullptr);
    bool areAllTablesExist(bool *allExist, QString *errorMessage = nullptr);
    bool tryCreateDatabaseIfMissing(QString *errorMessage = nullptr);
    bool createDatabase(QString *errorMessage = nullptr);

    QString m_configPath;
    QString m_host;
    QString m_dbName;
    QString m_user;
    QString m_password;
    int m_port = 5432;

    QSqlDatabase m_db;
    const QString m_connectionName = QStringLiteral("dbmanager_connection");
};
