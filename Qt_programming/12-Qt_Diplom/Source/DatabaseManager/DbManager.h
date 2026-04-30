#pragma once

#include <QHash>
#include <QSqlDatabase>
#include <QString>

class DbManager
{
public:
    // Конструктор: запоминает путь к config.ini для дальнейшего чтения настроек БД.
    explicit DbManager(QString configPath = QStringLiteral("config.ini"));
    // Деструктор: закрывает соединение с БД и освобождает именованное подключение Qt.
    ~DbManager();

    // Подключается к PostgreSQL по настройкам из ini, при необходимости создает БД.
    bool connectToDatabase(QString *errorMessage = nullptr);
    // Проверяет наличие таблиц и создает их при первом запуске.
    bool createTables(bool *tablesAlreadyExist = nullptr, QString *errorMessage = nullptr);
    // Сохраняет/обновляет частоту одного слова в одном документе.
    bool saveDocumentWordFrequency(const QString &documentPath,
                                   const QString &word,
                                   int frequency,
                                   QString *errorMessage = nullptr);
    // Сохраняет полный набор частот по документу, предварительно очищая старые связи.
    bool saveDocumentWordFrequencies(const QString &documentPath,
                                     const QHash<QString, int> &frequencies,
                                     QString *errorMessage = nullptr);
    // Возвращает состояние соединения с БД.
    bool isOpen() const;
    // Возвращает текущее подключение Qt SQL для выполнения внешних запросов.
    QSqlDatabase database() const;

private:
    // Создает или получает id документа по его пути.
    bool upsertDocument(const QString &documentPath, int *documentId, QString *errorMessage = nullptr);
    // Создает или получает id слова.
    bool upsertWord(const QString &word, int *wordId, QString *errorMessage = nullptr);
    // Создает или обновляет связь документ-слово с частотой.
    bool upsertDocumentWordFrequency(int documentId, int wordId, int frequency, QString *errorMessage = nullptr);

    // Читает параметры подключения к БД из секции [Database] ini-файла.
    bool loadConfig(QString *errorMessage = nullptr);
    // Проверяет, существуют ли все обязательные таблицы в схеме public.
    bool areAllTablesExist(bool *allExist, QString *errorMessage = nullptr);
    // Анализирует ошибку подключения и пытается создать БД, если ее нет.
    bool tryCreateDatabaseIfMissing(QString *errorMessage = nullptr);
    // Подключается к служебной БД postgres и выполняет CREATE DATABASE.
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
