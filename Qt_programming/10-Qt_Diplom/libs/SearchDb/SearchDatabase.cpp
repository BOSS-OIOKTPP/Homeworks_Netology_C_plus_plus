#include "SearchDatabase.h"

#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QSqlError>
#include <QSqlQuery>

namespace {

/// Чтение ключа секции [Database]: сначала с заглавной (Host), затем в нижнем регистре (host)
QString readDatabaseValue(const QSettings &s, const QString &keyTitle, const QString &keyLower,
                          const QString &defaultValue = QString())
{
    QString v = s.value(QStringLiteral("Database/%1").arg(keyTitle)).toString().trimmed();
    if (v.isEmpty())
        v = s.value(QStringLiteral("Database/%1").arg(keyLower)).toString().trimmed();
    if (v.isEmpty())
        v = defaultValue;
    return v;
}

} // namespace

SearchDatabase::SearchDatabase(QString connectionName)
    : m_connectionName(std::move(connectionName))
{}

SearchDatabase::~SearchDatabase()
{
    if (m_db.isValid() && m_db.isOpen())
        m_db.close();
    if (QSqlDatabase::contains(m_connectionName))
        QSqlDatabase::removeDatabase(m_connectionName);
}

bool SearchDatabase::openFromIni(const QString &iniFilePath)
{
    if (!QFile::exists(iniFilePath)) {
        qWarning() << "INI не найден:" << iniFilePath;
        return false;
    }

    // Стандартный разбор INI в Qt — класс QSettings (см. задание диплома)
    QSettings s(iniFilePath, QSettings::IniFormat);
    s.sync();
    if (s.status() != QSettings::NoError) {
        qWarning() << "Ошибка чтения INI:" << iniFilePath;
        return false;
    }

    const QString host = readDatabaseValue(s, QStringLiteral("Host"), QStringLiteral("host"),
                                            QStringLiteral("localhost"));
    const QString portStr = readDatabaseValue(s, QStringLiteral("Port"), QStringLiteral("port"),
                                              QStringLiteral("5432"));
    bool ok = false;
    const int port = portStr.toInt(&ok);
    const int portFinal = ok ? port : 5432;

    QString dbName = readDatabaseValue(s, QStringLiteral("Name"), QStringLiteral("dbname"));
    const QString user = readDatabaseValue(s, QStringLiteral("User"), QStringLiteral("user"));
    const QString password = readDatabaseValue(s, QStringLiteral("Password"), QStringLiteral("password"));

    if (dbName.isEmpty() || user.isEmpty()) {
        qWarning() << "В [Database] задайте Name (или dbname) и User (или user).";
        return false;
    }

    return open(host, portFinal, dbName, user, password);
}

bool SearchDatabase::open(const QString &host, int port, const QString &dbName,
                           const QString &user, const QString &password)
{
    if (QSqlDatabase::contains(m_connectionName))
        QSqlDatabase::removeDatabase(m_connectionName);

    m_db = QSqlDatabase::addDatabase(QStringLiteral("QPSQL"), m_connectionName);
    m_db.setHostName(host);
    m_db.setPort(port);
    m_db.setDatabaseName(dbName);
    m_db.setUserName(user);
    m_db.setPassword(password);

    if (!m_db.open()) {
        qWarning() << "QPSQL open:" << m_db.lastError().text();
        return false;
    }
    return true;
}

bool SearchDatabase::isOpen() const
{
    return m_db.isValid() && m_db.isOpen();
}

bool SearchDatabase::createTables()
{
    QSqlQuery q(m_db);

    const QString sqlDocs = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS documents ("
        "  id SERIAL PRIMARY KEY,"
        "  path TEXT NOT NULL UNIQUE"
        ");");

    const QString sqlWords = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS words ("
        "  id SERIAL PRIMARY KEY,"
        "  word TEXT NOT NULL UNIQUE"
        ");");

    const QString sqlDocWords = QStringLiteral(
        "CREATE TABLE IF NOT EXISTS document_words ("
        "  document_id INTEGER NOT NULL REFERENCES documents(id) ON DELETE CASCADE,"
        "  word_id INTEGER NOT NULL REFERENCES words(id) ON DELETE CASCADE,"
        "  frequency INTEGER NOT NULL CHECK (frequency > 0),"
        "  PRIMARY KEY (document_id, word_id)"
        ");");

    if (!q.exec(sqlDocs)) {
        qWarning() << "CREATE documents:" << q.lastError().text();
        return false;
    }
    if (!q.exec(sqlWords)) {
        qWarning() << "CREATE words:" << q.lastError().text();
        return false;
    }
    if (!q.exec(sqlDocWords)) {
        qWarning() << "CREATE document_words:" << q.lastError().text();
        return false;
    }
    return true;
}

bool SearchDatabase::truncateAll()
{
    QSqlQuery q(m_db);
    const QString sql = QStringLiteral(
        "TRUNCATE TABLE document_words, documents, words RESTART IDENTITY CASCADE;");
    if (!q.exec(sql)) {
        qWarning() << "TRUNCATE:" << q.lastError().text();
        return false;
    }
    return true;
}

QString SearchDatabase::databaseInfo() const
{
    if (!isOpen())
        return QStringLiteral("Нет подключения к базе данных.");

    QString s;
    s += QStringLiteral("База: %1\n").arg(m_db.databaseName());
    s += QStringLiteral("Пользователь: %1\n").arg(m_db.userName());
    s += QStringLiteral("Хост: %1\n").arg(m_db.hostName());
    s += QStringLiteral("Порт: %1\n").arg(m_db.port());
    return s;
}

qint64 SearchDatabase::getOrInsertWordId(const QString &word)
{
    QSqlQuery q(m_db);
    q.prepare(QStringLiteral(
        "INSERT INTO words (word) VALUES (:w) "
        "ON CONFLICT (word) DO UPDATE SET word = EXCLUDED.word "
        "RETURNING id;"));
    q.bindValue(QStringLiteral(":w"), word);
    if (!q.exec() || !q.next()) {
        qWarning() << "words:" << q.lastError().text();
        return -1;
    }
    return q.value(0).toLongLong();
}

qint64 SearchDatabase::insertDocumentRow(const QString &path)
{
    QSqlQuery q(m_db);
    q.prepare(QStringLiteral("INSERT INTO documents (path) VALUES (:p) RETURNING id;"));
    q.bindValue(QStringLiteral(":p"), path);
    if (!q.exec() || !q.next()) {
        qWarning() << "documents:" << q.lastError().text();
        return -1;
    }
    return q.value(0).toLongLong();
}

bool SearchDatabase::insertDocumentWord(qint64 docId, qint64 wordId, int frequency)
{
    QSqlQuery q(m_db);
    q.prepare(QStringLiteral(
        "INSERT INTO document_words (document_id, word_id, frequency) "
        "VALUES (:d, :w, :f);"));
    q.bindValue(QStringLiteral(":d"), docId);
    q.bindValue(QStringLiteral(":w"), wordId);
    q.bindValue(QStringLiteral(":f"), frequency);
    if (!q.exec()) {
        qWarning() << "document_words:" << q.lastError().text();
        return false;
    }
    return true;
}

bool SearchDatabase::saveIndexedDocument(const QString &filePath, const QHash<QString, int> &wordFreq)
{
    if (wordFreq.isEmpty())
        return true;

    const QString native = QDir::toNativeSeparators(filePath);
    const qint64 docId = insertDocumentRow(native);
    if (docId < 0)
        return false;

    for (auto it = wordFreq.constBegin(); it != wordFreq.constEnd(); ++it) {
        const qint64 wordId = getOrInsertWordId(it.key());
        if (wordId < 0)
            return false;
        if (!insertDocumentWord(docId, wordId, it.value()))
            return false;
    }
    return true;
}

bool SearchDatabase::search(const QStringList &queryWords, int maxResults,
                             QVector<QPair<QString, qint64>> *outHits, QString *errorMessage)
{
    outHits->clear();
    if (queryWords.isEmpty())
        return true;

    QStringList placeholders;
    for (int i = 0; i < queryWords.size(); ++i)
        placeholders << QStringLiteral(":w%1").arg(i);

    const QString sql = QStringLiteral(
        "SELECT d.path, SUM(dw.frequency) AS relevance "
        "FROM documents d "
        "INNER JOIN document_words dw ON dw.document_id = d.id "
        "INNER JOIN words w ON w.id = dw.word_id "
        "WHERE w.word IN (%1) "
        "GROUP BY d.id, d.path "
        "HAVING COUNT(DISTINCT w.word) = :n "
        "ORDER BY relevance DESC "
        "LIMIT %2")
                          .arg(placeholders.join(QStringLiteral(", ")))
                          .arg(maxResults);

    QSqlQuery q(m_db);
    q.prepare(sql);
    for (int i = 0; i < queryWords.size(); ++i)
        q.bindValue(QStringLiteral(":w%1").arg(i), queryWords.at(i));
    q.bindValue(QStringLiteral(":n"), queryWords.size());

    if (!q.exec()) {
        if (errorMessage)
            *errorMessage = q.lastError().text();
        return false;
    }

    while (q.next())
        outHits->append({q.value(0).toString(), q.value(1).toLongLong()});
    return true;
}

bool SearchDatabase::loadWordStatistics(QVector<QPair<QString, qint64>> *outRows, QString *errorMessage)
{
    outRows->clear();
    const QString sql = QStringLiteral(
        "SELECT w.word, COALESCE(SUM(dw.frequency), 0) AS total "
        "FROM words w "
        "LEFT JOIN document_words dw ON dw.word_id = w.id "
        "GROUP BY w.id, w.word "
        "ORDER BY w.word;");

    QSqlQuery q(m_db);
    if (!q.exec(sql)) {
        if (errorMessage)
            *errorMessage = q.lastError().text();
        return false;
    }

    while (q.next())
        outRows->append({q.value(0).toString(), q.value(1).toLongLong()});
    return true;
}
