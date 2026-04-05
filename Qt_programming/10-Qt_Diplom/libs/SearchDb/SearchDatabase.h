#pragma once

#include <QHash>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QSqlDatabase>
#include <QVector>

/**
 * Обёртка над QtSql (PostgreSQL / QPSQL) для дипломной поисковой системы.
 * По смыслу близко к классу DatabaseManager из FinalDiplom, но на Qt вместо libpqxx.
 */
class SearchDatabase {
public:
    explicit SearchDatabase(QString connectionName = QStringLiteral("diplom_db"));
    ~SearchDatabase();

    SearchDatabase(const SearchDatabase &) = delete;
    SearchDatabase &operator=(const SearchDatabase &) = delete;

    /// Читает секцию [Database] из INI через QSettings::IniFormat (ключи Host/Name или host/dbname)
    bool openFromIni(const QString &iniFilePath);

    bool isOpen() const;

    bool createTables();
    bool truncateAll();

    QString databaseInfo() const;

    /// Сохраняет один проиндексированный документ (путь + частоты слов)
    bool saveIndexedDocument(const QString &filePath, const QHash<QString, int> &wordFreq);

    /// Поиск: все слова из запроса должны быть в документе; сортировка по сумме частот
    bool search(const QStringList &queryWords, int maxResults,
                  QVector<QPair<QString, qint64>> *outHits, QString *errorMessage = nullptr);

    /// Все слова и суммарная частота по БД (для вкладки статистики)
    bool loadWordStatistics(QVector<QPair<QString, qint64>> *outRows, QString *errorMessage = nullptr);

    QSqlDatabase sqlDatabase() const { return m_db; }

private:
    bool open(const QString &host, int port, const QString &dbName,
              const QString &user, const QString &password);

    qint64 getOrInsertWordId(const QString &word);
    qint64 insertDocumentRow(const QString &path);
    bool insertDocumentWord(qint64 docId, qint64 wordId, int frequency);

    QString m_connectionName;
    QSqlDatabase m_db;
};
