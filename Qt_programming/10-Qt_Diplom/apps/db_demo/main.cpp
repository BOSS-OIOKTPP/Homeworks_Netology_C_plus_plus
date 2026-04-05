/**
 * Мини-тест модуля SearchDatabase: подключение к PostgreSQL, создание таблиц.
 * Запускайте после настройки db_demo.ini рядом с исполняемым файлом.
 */

#include "SearchDatabase.h"

#include <QCoreApplication>
#include <QDebug>

#ifdef _WIN32
#include <windows.h>
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
    SetConsoleCP(CP_UTF8);
    SetConsoleOutputCP(CP_UTF8);
#endif

    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName(QStringLiteral("DbDemo"));

    const QString iniPath = QCoreApplication::applicationDirPath() + QStringLiteral("/db_demo.ini");

    SearchDatabase db(QStringLiteral("db_demo_conn"));
    if (!db.openFromIni(iniPath)) {
        qWarning() << "Не удалось открыть БД. Положите db_demo.ini рядом с exe (см. db_demo.ini.example).";
        return 1;
    }

    qDebug().noquote() << QStringLiteral("--- Параметры соединения ---");
    qDebug().noquote() << db.databaseInfo();

    if (!db.createTables()) {
        qWarning() << "Ошибка CREATE TABLE";
        return 1;
    }

    qDebug().noquote() << QStringLiteral("Таблицы созданы (или уже существовали). Проверка пройдена.");
    return 0;
}
