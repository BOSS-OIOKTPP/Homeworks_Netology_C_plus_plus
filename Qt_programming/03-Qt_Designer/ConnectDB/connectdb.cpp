#include "connectdb.h"
#include <QMessageBox>
#include "./ui_connectdb.h"

ConnectDB::ConnectDB(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ConnectDB)
{

    // Сделаем следующие настройки
    // Qt::Dialog - окно станет диалоговым, т.е. убирет лишние иконки
    // Qt::WindowCloseButtonHint - оставляем только кнопку «Закрыть»
    // Qt::MSWindowsFixedSizeDialogHint - сообщаем Windows, что у окна фиксированный размер
//    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint | Qt::WindowTitleHint | Qt::WindowSystemMenuHint | Qt::WindowCloseButtonHint);

    setWindowFlags(Qt::WindowCloseButtonHint);


    ui->setupUi(this);
}

ConnectDB::~ConnectDB()
{
    delete ui;
}


void ConnectDB::on_buttonBox_clicked(QAbstractButton *button)
{
    // Выводим текст нажатой кнопки
    QMessageBox::information(this, "Сообщение", "Нажата кнопка: " + button->text());
    // Закрываем окно
    this->close();
}

