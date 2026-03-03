#include "dbdata.h"
#include "database.h"
#include "ui_dbdata.h"

DbData::DbData(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbData)
{
    ui->setupUi(this);

    //Ресайзим вектор значений, по количеству полей необходимых для
    //подключения к БД
    data.resize(NUM_DATA_FOR_CONNECT_TO_DB);

    //Единственное разумное значение по умолчанию — стандартный порт PostgreSQL.
    data[port] = QStringLiteral("5432");

    ui->le_host->setText(data[hostName]);
    ui->le_dbName->setText(data[dbName]);
    ui->le_login->setText(data[login]);
    ui->le_pass->setText(data[pass]);
    ui->spB_port->setValue(data[port].toInt());

}

DbData::~DbData()
{
    delete ui;
}

void DbData::setData(const QVector<QString> &dbData)
{
    data = dbData;
    if (data.size() < NUM_DATA_FOR_CONNECT_TO_DB) {
        data.resize(NUM_DATA_FOR_CONNECT_TO_DB);
    }
    if (data[port].trimmed().isEmpty()) {
        data[port] = QStringLiteral("5432");
    }

    ui->le_host->setText(data[hostName]);
    ui->le_dbName->setText(data[dbName]);
    ui->le_login->setText(data[login]);
    ui->le_pass->setText(data[pass]);
    ui->spB_port->setValue(data[port].toInt());
}
/*!
 * \brief Обработчик кнопки "Ок"
 */
void DbData::on_buttonBox_accepted()
{

    //Добавляем данные в контейнер и передаем в главное окно
    data[hostName] = ui->le_host->text();
    data[dbName] = ui->le_dbName->text();
    data[login] = ui->le_login->text();
    data[pass] = ui->le_pass->text();
    data[port] = QString::number(ui->spB_port->value());

    emit sig_sendData(data);

    accept();
}

