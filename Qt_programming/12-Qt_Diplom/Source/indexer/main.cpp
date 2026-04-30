#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QList>
#include <QSettings>

#include "../DatabaseManager/DbManager.h"
#include "Indexer.h"

static QString toRelativeForLog(const QString &absolutePath, const QString &baseDir)
{
    const QString relativePath = QDir(baseDir).relativeFilePath(absolutePath);
    return QDir::cleanPath(relativePath);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    const QString workingDir = QDir::currentPath();
    int logIndex = 1;

    auto logInfo = [&logIndex](const QString &message) {
        qInfo().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };
    auto logError = [&logIndex](const QString &message) {
        qCritical().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };

    logInfo(QStringLiteral("Тест модуля Indexer\nРабочий каталог: %1").arg(workingDir));

    const QString configPath =
        QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));

    {
        QSettings settings(configPath, QSettings::IniFormat);
        settings.beginGroup(QStringLiteral("Paths"));
        settings.setValue(QStringLiteral("roots"),
                          QStringList{QStringLiteral("c:\\Tmp\\Work\\Documents"),
                                      QStringLiteral("c:\\Tmp\\Work2\\Documents")});
        settings.endGroup();
        settings.sync();
    }
    logInfo(QStringLiteral("Тестовая запись roots (2 пути) через QSettings: Выполнено."));

    DbManager dbManager(configPath);
    QString errorMessage;
    if (!dbManager.connectToDatabase(&errorMessage)) {
        logError(QStringLiteral("Подключение к БД по конфигурации %1: ОШИБКА: %2")
                     .arg(toRelativeForLog(configPath, workingDir), errorMessage));
        return 1;
    }
    logInfo(QStringLiteral("Подключение к БД по конфигурации %1: Подключение к БД выполнено.")
                .arg(toRelativeForLog(configPath, workingDir)));

    bool tablesAlreadyExist = false;
    if (!dbManager.createTables(&tablesAlreadyExist, &errorMessage)) {
        logError(QStringLiteral("Проверка существования таблиц: ОШИБКА: %1").arg(errorMessage));
        return 2;
    }
    if (tablesAlreadyExist) {
        logInfo(QStringLiteral("Проверка существования таблиц: Таблицы существуют."));
    } else {
        logInfo(QStringLiteral("Проверка существования таблиц: Таблицы не существуют - выполнено создание таблиц."));
    }

    Indexer indexer(&dbManager, configPath);
    if (!indexer.loadSettings(&errorMessage)) {
        logError(QStringLiteral("Чтение настроек индексатора: ОШИБКА: %1").arg(errorMessage));
        return 3;
    }
    logInfo(QStringLiteral("Чтение настроек индексатора: Выполнено."));

    int indexedFilesCount = 0;
    int indexedWordsCount = 0;
    QList<Indexer::FileStat> fileStats;
    if (!indexer.runIndexing(&indexedFilesCount, &indexedWordsCount, &fileStats, &errorMessage)) {
        logError(QStringLiteral("Индексация файлов: ОШИБКА: %1").arg(errorMessage));
        return 4;
    }
    const QStringList roots = indexer.rootPaths();
    for (const QString &root : roots) {
        QList<Indexer::FileStat> rootStats;
        for (const Indexer::FileStat &stat : fileStats) {
            if (QDir::fromNativeSeparators(stat.rootPathForLog) == QDir::fromNativeSeparators(root)) {
                rootStats.append(stat);
            }
        }

        int rootFilesCount = rootStats.size();
        int rootWordsCount = 0;
        for (const Indexer::FileStat &stat : rootStats) {
            rootWordsCount += stat.savedWords;
        }

        logInfo(QStringLiteral("Каталог(и) для индексации файлов: %1")
                    .arg(QDir::fromNativeSeparators(root)));
        qInfo().noquote() << QStringLiteral("   Индексация файлов: Выполнено. Проиндексировано файлов: %1, "
                                            "уникальных слов: %2.")
                                 .arg(rootFilesCount)
                                 .arg(rootWordsCount);
        qInfo().noquote() << QStringLiteral("   Статистика по файлам:");
        for (const Indexer::FileStat &stat : rootStats) {
            qInfo().noquote() << QStringLiteral("    %1 - слов всего: %2, уникальных: %3, сохранено в БД: %4.")
                                     .arg(stat.pathForLog)
                                     .arg(stat.totalWords)
                                     .arg(stat.uniqueWords)
                                     .arg(stat.savedWords);
        }
    }

    logInfo(QStringLiteral("Тест завершен успешно."));
    return 0;
}
