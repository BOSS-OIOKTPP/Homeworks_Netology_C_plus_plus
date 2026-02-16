#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ГРУППА 1
    ui->groupBox->setTitle("Радиокнопки");  // Изменяем название группы
    ui->radioButton->setText("Радиокнопка 1");
    ui->radioButton_2->setText("Радиокнопка 2");  

    // ГРУППА 2
    ui->groupBox_2->setTitle("Выпадающий список");  // Изменяем название группы
    ui->comboBox->addItem("Значение 1");
    ui->comboBox->addItem("Значение 2");
    ui->comboBox->addItem("Значение 3");
    ui->comboBox->setCurrentIndex(1);
    ui->label->setText("Описание");

    // ГРУППА 3
    ui->groupBox_3->setTitle("Тумблер");  // Изменяем название группы
    ui->pushButton->setCheckable(true);   // Превращаем кнопку в тумблер
    ui->pushButton->setChecked(true);
    ui->pushButton->setText("Включено");

    // ГРУППА 4
    ui->groupBox_4->setTitle("Индикатор выполнения");  // Изменяем название группы
    ui->progressBar->setMinimum(0);      // Минимальное значение
    ui->progressBar->setMaximum(1000);    // Максимальное значение (100%)
    ui->progressBar->setValue(150);       // Текущее значение (начальное)
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked(bool checked)
{
    if (checked==true) {
        ui->pushButton->setText("Включено");
    }
    else {
        ui->pushButton->setText("Выключено");
    }
}


void MainWindow::on_pushButton_2_clicked()
{
    // Получаем текущее значение
    int currentValue = ui->progressBar->value();
    int maxValue = ui->progressBar->maximum();
    int minValue = ui->progressBar->minimum();

    // Увеличиваем на 10%
    int newValue = currentValue + 10*(maxValue - minValue)/100;

    // Проверка: если новое значение больше 100, сбрасываем на 0
    if (newValue > maxValue) {
        newValue = minValue;
    }

    // Устанавливаем новое значение
    ui->progressBar->setValue(newValue);


}

