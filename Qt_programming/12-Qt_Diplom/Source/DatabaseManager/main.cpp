#include <QCoreApplication>
#include <QDebug>
#include <QDir>
#include <QList>

#include "DbManager.h"

// Преобразует абсолютный путь в относительный, чтобы лог был короче и понятнее.
static QString toRelativeForLog(const QString &absolutePath, const QString &baseDir)
{
    const QString relativePath = QDir(baseDir).relativeFilePath(absolutePath);
    return QDir::cleanPath(relativePath);
}

int main(int argc, char *argv[])
{
    // Инициализация приложения
    QCoreApplication a(argc, argv);
    // Рабочий каталог процесса: используем в стартовом логе.
    const QString workingDir = QDir::currentPath();
    // Сквозная нумерация шагов теста.
    int logIndex = 1;

    // Локальная функция для информационных сообщений.
    auto logInfo = [&logIndex](const QString &message) {
        qInfo().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };
    // Локальная функция для сообщений об ошибках.
    auto logError = [&logIndex](const QString &message) {
        qCritical().noquote() << QStringLiteral("%1) %2").arg(logIndex++).arg(message);
    };

    // Сообщаем о старте тестового сценария.
    logInfo(QStringLiteral("Тест модуля DatabaseManager\nРабочий каталог: %1").arg(workingDir));

    // Файл конфигурации должен лежать рядом с исполняемым файлом.
    const QString configPath =
        QDir(QCoreApplication::applicationDirPath()).absoluteFilePath(QStringLiteral("config.ini"));

    // Создаем объект работы с БД по настройкам из config.ini.
    DbManager dbManager(configPath);
    QString errorMessage;

    // Подключаемся к PostgreSQL.
    if (!dbManager.connectToDatabase(&errorMessage)) {
        logError(QStringLiteral("Подключение к БД по конфигурации %1: ОШИБКА: %2")
                     .arg(toRelativeForLog(configPath, workingDir), errorMessage));
        return 1;
    }
    logInfo(QStringLiteral("Подключение к БД по конфигурации %1: Подключение к БД выполнено.")
                .arg(toRelativeForLog(configPath, workingDir)));

    // Проверяем наличие таблиц и при необходимости создаем их.
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

    // Структура одной тестовой записи для заполнения БД.
    struct TestRecord {
        QString documentPath;
        QString word;
        int frequency = 0;
    };

    // Набор тестовых данных: документ, слово, частота.
    const QList<TestRecord> testRecords = {
        {QStringLiteral("docs/doc1.txt"), QStringLiteral("qt6.4.2"), 5},
        {QStringLiteral("docs/doc2.txt"), QStringLiteral("database"), 3},
        {QStringLiteral("docs/doc3.txt"), QStringLiteral("search"), 7}
    };

    // Пишем в лог, сколько тестовых записей будет сохранено.
    logInfo(QStringLiteral("Тестовое заполнение таблиц: подготовлено %1 записи(ей).").arg(testRecords.size()));

    // По очереди сохраняем тестовые данные в БД через DbManager.
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

    // Успешное завершение теста DatabaseManager.
    logInfo(QStringLiteral("Тест завершен успешно."));
    return 0;
}
