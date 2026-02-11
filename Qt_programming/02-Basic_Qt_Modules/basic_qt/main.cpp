#include <QCoreApplication>
#include <QSqlDatabase>
#include <QSqlError>
#include <QHostAddress>


int main(int argc, char *argv[])
{
    // Инициализация Qt
    QCoreApplication app(argc, argv);

    // Смотрим какие драйверы установлены
    //qInfo() << "Доступные драйверы БД:" << QSqlDatabase::drivers();

    //---------------------   1   ----------------------------------
    // Работа с БД
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setHostName("localhost");
    db.setDatabaseName("postgres");
    db.setUserName("postgres");
    db.setPassword("1");

    if (db.open()) {
        qInfo() << "Соединение установлено";
        db.close();
    } else {
        qWarning() << "Ошибка:" << db.lastError().text();
        return 1;
    }


    //---------------------   2   ----------------------------------
    // Работа с сетью
    QHostAddress myAddress("127.0.0.1");
    qInfo() << "Мой IP адрес:" << myAddress.toString();


    return 0;
}
