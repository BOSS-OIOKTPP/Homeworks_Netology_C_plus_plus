#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QList>

#include "DbManager.h"

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

    logInfo(QStringLiteral("Тест модуля DatabaseManager\nРабочий каталог: %1").arg(workingDir));

    // Файл конфигурации должен лежать рядом с исполняемым файлом.
    const QString configPath =
        QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));
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

    struct TestRecord {
        QString documentPath;
        QString word;
        int frequency = 0;
    };

    const QList<TestRecord> testRecords = {
        {QStringLiteral("docs/doc1.txt"), QStringLiteral("qt6.4.2"), 5},
        {QStringLiteral("docs/doc2.txt"), QStringLiteral("database"), 3},
        {QStringLiteral("docs/doc3.txt"), QStringLiteral("search"), 7}
    };

    logInfo(QStringLiteral("Тестовое заполнение таблиц: подготовлено %1 записи(ей).").arg(testRecords.size()));
    for (int i = 0; i < testRecords.size(); ++i) {
        const TestRecord &record = testRecords.at(i);
        if (!dbManager.saveDocumentWordFrequency(record.documentPath, record.word, record.frequency, &errorMessage)) {
            logError(QStringLiteral("Тестовое заполнение записи %1: ОШИБКА: %2").arg(i + 1).arg(errorMessage));
            return 3;
        }
        logInfo(QStringLiteral("Тестовое заполнение записи %1: УСПЕХ (%2, %3, частота=%4).")
                    .arg(i + 1)
                    .arg(record.documentPath, record.word)
                    .arg(record.frequency));
    }

    logInfo(QStringLiteral("Тест завершен успешно."));
    return 0;
}
