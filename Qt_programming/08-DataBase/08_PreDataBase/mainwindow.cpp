#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QHeaderView>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    //Исходное состояние виджетов
    ui->setupUi(this);
    ui->lb_statusConnect->setStyleSheet("color:red");
    ui->pb_request->setEnabled(false);
    ui->tb_result->setColumnCount(2);
    ui->tb_result->setHorizontalHeaderLabels({QStringLiteral("Название фильма"),
                                              QStringLiteral("Описание фильма")});

    /*
     * Выделим память под необходимые объекты. Все они наследники
     * QObject, поэтому воспользуемся иерархией.
    */

    dataDb = new DbData(this);
    dataBase = new DataBase(this);
    msg = new QMessageBox(this);

    //Установим размер вектора данных для подключения к БД
    dataForConnect.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    //Параметры по умолчанию: используются при "Подключиться"
    dataForConnect[hostName] = QStringLiteral("981757-ca08998.tmweb.ru");
    dataForConnect[dbName] = QStringLiteral("netology_cpp");
    dataForConnect[login] = QStringLiteral("netology_usr_cpp");
    dataForConnect[pass] = QStringLiteral("CppNeto3");
    dataForConnect[port] = QStringLiteral("5432");

    //Форма ввода должна открываться уже заполненной текущими значениями
    dataDb->setData(dataForConnect);

    /*
     * Добавим БД используя стандартный драйвер PSQL и зададим имя.
    */
    dataBase->AddDataBase(POSTGRE_DRIVER, DB_NAME);

    /*
     * Устанавливаем данные для подключениея к БД.
     * Поскольку метод небольшой используем лямбда-функцию.
     */
    connect(dataDb, &DbData::sig_sendData, this, [&](QVector<QString> receivData){
        dataForConnect = receivData;
    });

    /*
     * Соединяем сигнал, который передает ответ от БД с методом, который отображает ответ в ПИ
     */
//    connect(dataBase, &DataBase::sig_SendDataFromDB, this, &MainWindow::ScreenDataFromDB);

    /*
     *  Сигнал для подключения к БД
     */
    connect(dataBase, &DataBase::sig_SendStatusConnection, this, &MainWindow::ReceiveStatusConnectionToDB);

}

MainWindow::~MainWindow()
{
    delete ui;
}

/*!
 * @brief Слот отображает форму для ввода данных подключения к БД
 */
void MainWindow::on_act_addData_triggered()
{
    //Покажем форму с текущими параметрами (сначала — дефолтными)
    dataDb->setData(dataForConnect);
    if (dataDb->exec() != QDialog::Accepted) {
        return;
    }

    //После изменения параметров сразу выполняем подключение
    if (ui->lb_statusConnect->text() != "Отключено") {
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->pb_request->setEnabled(false);
    }

    ui->lb_statusConnect->setText("Подключение");
    ui->lb_statusConnect->setStyleSheet("color : black");

    auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
    (void)QtConcurrent::run(conn);
}

/*!
 * @brief Слот выполняет подключение к БД. И отображает ошибки.
 */

void MainWindow::on_act_connect_triggered()
{
    /*
     * Обработчик кнопки у нас должен подключаться и отключаться от БД.
     * Можно привязаться к надписи лейбла статуса. Если он равен
     * "Отключено" мы осуществляем подключение, если "Подключено" то
     * отключаемся
    */

    if(ui->lb_statusConnect->text() == "Отключено"){

       ui->lb_statusConnect->setText("Подключение");
       ui->lb_statusConnect->setStyleSheet("color : black");

       auto conn = [&]{dataBase->ConnectToDataBase(dataForConnect);};
       (void)QtConcurrent::run(conn);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        ui->lb_statusConnect->setText("Отключено");
        ui->act_connect->setText("Подключиться");
        ui->lb_statusConnect->setStyleSheet("color:red");
        ui->pb_request->setEnabled(false);

    }

}

/*!
 * \brief Обработчик кнопки "Получить"
 */
void MainWindow::on_pb_request_clicked()
{
    QSqlDatabase db = QSqlDatabase::database(DB_NAME);

    int filterIdx = ui->cb_category->currentIndex();

    ui->tb_result->setRowCount(0);

    if (filterIdx == 0) {
        // Все фильмы через QSqlTableModel
        QSqlTableModel model(this, db);
        model.setTable("film");
        model.select();

        int titleCol = model.fieldIndex("title");
        int descCol  = model.fieldIndex("description");

        int rows = model.rowCount();
        ui->tb_result->setRowCount(rows);

        for (int r = 0; r < rows; ++r) {
            ui->tb_result->setItem(r, 0, new QTableWidgetItem(model.data(model.index(r, titleCol)).toString()));
            ui->tb_result->setItem(r, 1, new QTableWidgetItem(model.data(model.index(r, descCol)).toString()));
        }
    } else {
        // Комедия / Ужасы через QSqlQueryModel
        QString category = (filterIdx == 1) ? "Comedy" : "Horror";

        QSqlQueryModel model;
        model.setQuery(
            "SELECT f.title, f.description "
            "FROM film f "
            "JOIN film_category fc ON f.film_id = fc.film_id "
            "JOIN category c ON c.category_id = fc.category_id "
            "WHERE c.name = '" + category + "' "
            "ORDER BY f.title",
            db);

        int rows = model.rowCount();
        ui->tb_result->setRowCount(rows);

        for (int r = 0; r < rows; ++r) {
            ui->tb_result->setItem(r, 0, new QTableWidgetItem(model.data(model.index(r, 0)).toString()));
            ui->tb_result->setItem(r, 1, new QTableWidgetItem(model.data(model.index(r, 1)).toString()));
        }
    }

}

/*!
 * \brief Слот отображает значение в QTableWidget
 * \param widget
 * \param typeRequest
 */
//void MainWindow::ScreenDataFromDB(const QTableWidget *widget, int typeRequest)
//{
//
//    ///Тут должен быть код ДЗ
//
//}

void MainWindow::on_pb_clear_clicked()
{
    ui->tb_result->setRowCount(0); // Удаляет все строки
    ui->tb_result->setColumnCount(2);
    ui->tb_result->setHorizontalHeaderLabels({QStringLiteral("Название фильма"),
                                              QStringLiteral("Описание фильма")});
}
/*!
 * \brief Метод изменяет стотояние формы в зависимости от статуса подключения к БД
 * \param status
 */
void MainWindow::ReceiveStatusConnectionToDB(bool status)
{
    if(status){
        ui->act_connect->setText("Отключиться");
        ui->lb_statusConnect->setText("Подключено к БД");
        ui->lb_statusConnect->setStyleSheet("color:green");
        ui->pb_request->setEnabled(true);
    }
    else{
        dataBase->DisconnectFromDataBase(DB_NAME);
        msg->setIcon(QMessageBox::Critical);
        msg->setText(dataBase->GetLastError().text());
        ui->lb_statusConnect->setText("Отключено");
        ui->lb_statusConnect->setStyleSheet("color:red");
        msg->exec();
    }

}


