#include "DatabaseManager.h"

#include <QCoreApplication>
#include <QSettings>
#include <QTextStream>
#include <cstdlib>

static DbConfig readConfig(const QString& iniPath)
{
    QSettings settings(iniPath, QSettings::IniFormat);

    DbConfig config;
    config.host = settings.value("Database/Host", "localhost").toString();
    config.port = settings.value("Database/Port", 5432).toInt();
    config.databaseName = settings.value("Database/Name", "spider_db").toString();
    config.user = settings.value("Database/User", "spider_user").toString();
    config.password = settings.value("Database/Password", "").toString();

    config.adminDatabase = settings.value("Database/AdminDatabase", "postgres").toString();
    config.adminUser = settings.value("Database/AdminUser", "").toString();
    config.adminPassword = settings.value("Database/AdminPassword", "").toString();

    return config;
}

int main(int argc, char* argv[])
{
    QCoreApplication app(argc, argv);
    QTextStream out(stdout);
    QTextStream err(stderr);

    const QString iniPath = QCoreApplication::applicationDirPath() + "/config.ini";
    const DbConfig config = readConfig(iniPath);

    DatabaseManager databaseManager(config);

    QString errorMessage;
    if (!databaseManager.ensureDatabaseAndConnect(&errorMessage)) {
        err << "Ошибка подключения/создания БД: " << errorMessage << Qt::endl;
        return EXIT_FAILURE;
    }

    if (!databaseManager.ensureSchema(&errorMessage)) {
        err << "Ошибка создания таблиц: " << errorMessage << Qt::endl;
        return EXIT_FAILURE;
    }

    out << "Готово: БД доступна, таблицы созданы или уже существовали." << Qt::endl;
    return EXIT_SUCCESS;
}
