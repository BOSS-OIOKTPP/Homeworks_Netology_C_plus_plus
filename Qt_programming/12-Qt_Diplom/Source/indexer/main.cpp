#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QList>
#include <iostream>

#include "../DatabaseManager/DbManager.h"
#include "Indexer.h"

#ifdef Q_OS_WIN
#include <windows.h>
#endif

// Преобразует абсолютный путь в относительный для более короткого и удобного лога.
static QString toRelativeForLog(const QString &absolutePath, const QString &baseDir)
{
    const QString relativePath = QDir(baseDir).relativeFilePath(absolutePath);
    return QDir::cleanPath(relativePath);
}

int main(int argc, char *argv[])
{
#ifdef Q_OS_WIN
    // Синхронизируем кодировку консоли с системной ANSI-кодировкой,
    // чтобы русский текст от qInfo/qCritical отображался без "иероглифов".
    const UINT ansiCodePage = GetACP();
    SetConsoleOutputCP(ansiCodePage);
    SetConsoleCP(ansiCodePage);
#endif

    // Инициализация консольного Qt-приложения.
    QCoreApplication a(argc, argv);
    // Рабочий каталог процесса: используем в диагностике и для красивого вывода путей.
    const QString workingDir = QDir::currentPath();
    // Общий счетчик шагов, чтобы лог был нумерованным.
    int logIndex = 1;

    // Локальная функция для информационных сообщений.
    auto logInfo = [&logIndex](const QString &message) {
        qInfo().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };
    // Локальная функция для сообщений об ошибках.
    auto logError = [&logIndex](const QString &message) {
        qCritical().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };
    // Пауза перед завершением, чтобы окно консоли не закрывалось сразу.
    auto waitForEnter = []() {
        qInfo().noquote() << QStringLiteral("\nНажмите Enter для завершения...");
        std::cin.get();
    };

    // Стартовый лог с краткой информацией о запуске.
    logInfo(QStringLiteral("Запуск модуля Indexer\nРабочий каталог: %1").arg(workingDir));

    // Ожидаем config.ini рядом с исполняемым файлом.
    const QString configPath =
        QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));

    // Создаем менеджер БД и выполняем подключение по параметрам из config.ini.
    DbManager dbManager(configPath);
    QString errorMessage;
    if (!dbManager.connectToDatabase(&errorMessage)) {
        logError(QStringLiteral("Подключение к БД по конфигурации %1: ОШИБКА: %2")
                     .arg(toRelativeForLog(configPath, workingDir), errorMessage));
        waitForEnter();
        return 1;
    }
    logInfo(QStringLiteral("Подключение к БД по конфигурации %1: Подключение к БД выполнено.")
                .arg(toRelativeForLog(configPath, workingDir)));

    // Проверяем, есть ли рабочие таблицы. При их отсутствии создаем автоматически.
    bool tablesAlreadyExist = false;
    if (!dbManager.createTables(&tablesAlreadyExist, &errorMessage)) {
        logError(QStringLiteral("Проверка существования таблиц: ОШИБКА: %1").arg(errorMessage));
        waitForEnter();
        return 2;
    }
    if (tablesAlreadyExist) {
        logInfo(QStringLiteral("Проверка существования таблиц: Таблицы существуют."));
    } else {
        logInfo(QStringLiteral("Проверка существования таблиц: Таблицы не существуют - выполнено создание таблиц."));
    }

    // Создаем индексатор и загружаем настройки секции [Paths] из config.ini.
    Indexer indexer(&dbManager, configPath);
    if (!indexer.loadSettings(&errorMessage)) {
        logError(QStringLiteral("Чтение настроек индексатора: ОШИБКА: %1").arg(errorMessage));
        waitForEnter();
        return 3;
    }
    logInfo(QStringLiteral("Чтение настроек индексатора: Выполнено."));

    // Запускаем индексацию и собираем общую статистику + статистику по каждому файлу.
    int indexedFilesCount = 0;
    int indexedWordsCount = 0;
    QList<Indexer::FileStat> fileStats;
    if (!indexer.runIndexing(&indexedFilesCount, &indexedWordsCount, &fileStats, &errorMessage)) {
        logError(QStringLiteral("Индексация файлов: ОШИБКА: %1").arg(errorMessage));
        waitForEnter();
        return 4;
    }

    // Выводим статистику отдельно по каждому корневому каталогу из настроек.
    const QStringList roots = indexer.rootPaths();
    for (const QString &root : roots) {
        // Отбираем только те файлы, которые относятся к текущему корню.
        QList<Indexer::FileStat> rootStats;
        for (const Indexer::FileStat &stat : fileStats) {
            if (QDir::fromNativeSeparators(stat.rootPathForLog) == QDir::fromNativeSeparators(root)) {
                rootStats.append(stat);
            }
        }

        // Считаем агрегаты по корню: число файлов и суммарное число уникальных слов, сохраненных в БД.
        int rootFilesCount = rootStats.size();
        int rootWordsCount = 0;
        for (const Indexer::FileStat &stat : rootStats) {
            rootWordsCount += stat.savedWords;
        }

        // Печатаем блок сводной статистики по корню.
        logInfo(QStringLiteral("Каталог(и) для индексации файлов: %1")
                    .arg(QDir::fromNativeSeparators(root)));
        qInfo().noquote() << QStringLiteral("   Индексация файлов: Выполнено. Проиндексировано файлов: %1, "
                                            "уникальных слов: %2.")
                                 .arg(rootFilesCount)
                                 .arg(rootWordsCount);
        qInfo().noquote() << QStringLiteral("   Статистика по файлам:");

        // Печатаем подробную статистику по каждому проиндексированному файлу.
        for (const Indexer::FileStat &stat : rootStats) {
            qInfo().noquote() << QStringLiteral("    %1 - слов всего: %2, уникальных: %3, сохранено в БД: %4.")
                                     .arg(stat.pathForLog)
                                     .arg(stat.totalWords)
                                     .arg(stat.uniqueWords)
                                     .arg(stat.savedWords);
        }
    }

    // Успешное завершение тестового сценария.
    logInfo(QStringLiteral("Программа завершена успешно."));
    waitForEnter();
    return 0;
}
