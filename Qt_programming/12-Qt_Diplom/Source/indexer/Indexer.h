#pragma once

#include <QList>
#include <QString>
#include <QStringList>

class DbManager;

class Indexer
{
public:
    // Статистика обработки одного файла для вывода в лог.
    struct FileStat {
        QString rootPathForLog;
        QString pathForLog;
        int totalWords = 0;
        int uniqueWords = 0;
        int savedWords = 0;
    };

    // Конструктор индексатора: принимает объект работы с БД и путь к config.ini.
    explicit Indexer(DbManager *dbManager, QString configPath = QStringLiteral("config.ini"));

    // Читает настройки [Paths] из ini (корневые каталоги и расширения файлов).
    bool loadSettings(QString *errorMessage = nullptr);
    // Запускает рекурсивную индексацию файлов и возвращает общую/пофайловую статистику.
    bool runIndexing(int *indexedFilesCount = nullptr,
                     int *indexedWordsCount = nullptr,
                     QList<FileStat> *fileStats = nullptr,
                     QString *errorMessage = nullptr);
    // Возвращает список корневых каталогов, загруженных из настроек.
    QStringList rootPaths() const;

private:
    // Проверяет, подходит ли файл под список разрешенных расширений.
    bool shouldIndexFile(const QString &filePath) const;
    // Индексирует один файл: читает текст, считает частоты слов, сохраняет в БД.
    bool indexSingleFile(const QString &filePath,
                         int *savedWordsCount,
                         int *totalWordsCount,
                         int *uniqueWordsCount,
                         QString *errorMessage = nullptr);

    DbManager *m_dbManager = nullptr;
    QString m_configPath;
    QStringList m_rootPaths;
    QStringList m_extensions;
};

