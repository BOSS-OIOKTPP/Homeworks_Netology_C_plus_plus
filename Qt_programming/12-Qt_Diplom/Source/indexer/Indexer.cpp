#include "Indexer.h"

#include "../DatabaseManager/DbManager.h"

#include <QDir>
#include <QDirIterator>
#include <QFile>
#include <QFileInfo>
#include <QHash>
#include <QRegularExpression>
#include <QSettings>
#include <QStringConverter>
#include <QStringDecoder>

Indexer::Indexer(DbManager *dbManager, QString configPath)
    : m_dbManager(dbManager)
    , m_configPath(std::move(configPath))
{
}

// Загружает секцию [Paths] из ini и подготавливает списки каталогов/расширений.
bool Indexer::loadSettings(QString *errorMessage)
{
    QSettings settings(m_configPath, QSettings::IniFormat);

    if (!settings.childGroups().contains(QStringLiteral("Paths"))) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("В файле конфигурации отсутствует секция [Paths]: %1").arg(m_configPath);
        }
        return false;
    }

    settings.beginGroup(QStringLiteral("Paths"));
    const QVariant rootsValue = settings.value(QStringLiteral("roots"));
    QString rootsRaw = rootsValue.toString();
    if (rootsRaw.isEmpty()) {
        const QStringList rootsList = rootsValue.toStringList();
        if (!rootsList.isEmpty()) {
            rootsRaw = rootsList.join(',');
        }
    }
    QString extensionsRaw = settings.value(QStringLiteral("extensions")).toString();

    // Поддержка ini с пробелами вокруг '=' (например, "roots = ...").
    // В некоторых случаях такие ключи могут считаться как "roots " и "extensions ".
    const QStringList keys = settings.childKeys();
    for (const QString &key : keys) {
        const QString trimmedKey = key.trimmed().toLower();
        if (rootsRaw.isEmpty() && trimmedKey == QStringLiteral("roots")) {
            rootsRaw = settings.value(key).toString();
        } else if (extensionsRaw.isEmpty() && trimmedKey == QStringLiteral("extensions")) {
            extensionsRaw = settings.value(key).toString();
        }
    }
    settings.endGroup();

    m_rootPaths.clear();
    m_extensions.clear();

    // Поддержка нескольких корневых каталогов:
    // roots="c:/Dir1;c:/Dir2" или roots="c:/Dir1,c:/Dir2".
    const QStringList roots = rootsRaw.split(QRegularExpression(QStringLiteral("[;,]")), Qt::SkipEmptyParts);
    for (const QString &root : roots) {
        const QString normalized = QDir::fromNativeSeparators(root.trimmed());
        if (!normalized.isEmpty()) {
            m_rootPaths.append(normalized);
        }
    }

    const QStringList extensions = extensionsRaw.split(',', Qt::SkipEmptyParts);
    for (const QString &extension : extensions) {
        QString ext = extension.trimmed().toLower();
        if (ext.startsWith('.')) {
            ext.remove(0, 1);
        }
        if (!ext.isEmpty()) {
            m_extensions.append(ext);
        }
    }

    if (m_rootPaths.isEmpty() || m_extensions.isEmpty()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Секция [Paths] заполнена не полностью в файле: %1").arg(m_configPath);
        }
        return false;
    }

    return true;
}

// Выполняет полный проход по каталогам и индексирует подходящие файлы.
bool Indexer::runIndexing(int *indexedFilesCount,
                          int *indexedWordsCount,
                          QList<FileStat> *fileStats,
                          QString *errorMessage)
{
    if (m_dbManager == nullptr || !m_dbManager->isOpen()) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("DbManager не инициализирован или соединение с БД не открыто.");
        }
        return false;
    }

    int filesCount = 0;
    int wordsCount = 0;

    if (fileStats != nullptr) {
        fileStats->clear();
    }

    for (const QString &rootPath : m_rootPaths) {
        QDir rootDir(rootPath);
        if (!rootDir.exists()) {
            continue;
        }

        QDirIterator it(rootPath, QDir::Files, QDirIterator::Subdirectories);
        while (it.hasNext()) {
            const QString filePath = it.next();
            if (!shouldIndexFile(filePath)) {
                continue;
            }

            int savedWordsCount = 0;
            int totalWordsCount = 0;
            int uniqueWordsCount = 0;
            if (!indexSingleFile(filePath, &savedWordsCount, &totalWordsCount, &uniqueWordsCount, errorMessage)) {
                return false;
            }

            ++filesCount;
            wordsCount += savedWordsCount;

            if (fileStats != nullptr) {
                FileStat stat;
                stat.rootPathForLog = QDir::fromNativeSeparators(rootPath);
                stat.pathForLog = QDir(rootPath).relativeFilePath(filePath);
                stat.totalWords = totalWordsCount;
                stat.uniqueWords = uniqueWordsCount;
                stat.savedWords = savedWordsCount;
                fileStats->append(stat);
            }
        }
    }

    if (indexedFilesCount != nullptr) {
        *indexedFilesCount = filesCount;
    }
    if (indexedWordsCount != nullptr) {
        *indexedWordsCount = wordsCount;
    }
    return true;
}

// Возвращает корневые каталоги, загруженные из конфигурации.
QStringList Indexer::rootPaths() const
{
    return m_rootPaths;
}

// Определяет, нужно ли индексировать файл по его расширению.
bool Indexer::shouldIndexFile(const QString &filePath) const
{
    const QString suffix = QFileInfo(filePath).suffix().toLower();
    return m_extensions.contains(suffix);
}

// Индексирует содержимое одного файла и сохраняет итоговые частоты слов в БД.
bool Indexer::indexSingleFile(const QString &filePath,
                              int *savedWordsCount,
                              int *totalWordsCount,
                              int *uniqueWordsCount,
                              QString *errorMessage)
{
    if (savedWordsCount == nullptr || totalWordsCount == nullptr || uniqueWordsCount == nullptr) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Внутренняя ошибка: не переданы указатели статистики файла.");
        }
        return false;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось открыть файл '%1'.").arg(filePath);
        }
        return false;
    }

    const QByteArray bytes = file.readAll();
    file.close();

    QStringDecoder decoder(QStringDecoder::Utf8);
    QString text = decoder.decode(bytes);
    if (decoder.hasError()) {
        text = QString::fromLocal8Bit(bytes);
    }

    const QRegularExpression separatorPattern(QStringLiteral("[^\\p{L}\\p{N}]+"));
    const QStringList tokens = text.split(separatorPattern, Qt::SkipEmptyParts);

    QHash<QString, int> frequencies;
    *totalWordsCount = 0;
    for (const QString &token : tokens) {
        const QString word = token.toLower();
        if (word.length() <= 3 || word.length() > 32) {
            continue;
        }
        ++(*totalWordsCount);
        ++frequencies[word];
    }

    *uniqueWordsCount = frequencies.size();

    QString dbError;
    if (!m_dbManager->saveDocumentWordFrequencies(filePath, frequencies, &dbError)) {
        if (errorMessage != nullptr) {
            *errorMessage = QStringLiteral("Не удалось сохранить индекс для файла '%1': %2")
                                .arg(filePath, dbError);
        }
        return false;
    }
    *savedWordsCount = frequencies.size();

    return true;
}

