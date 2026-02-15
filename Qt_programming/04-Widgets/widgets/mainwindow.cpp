#include "mainwindow.h"
#include "./ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // ГРУППА 1
    // Изменяем название радиокнопок
    ui->radioButton->setText("Радиокнопка 1");
    ui->radioButton_2->setText("Радиокнопка 2");

    ui->groupBox->setTitle("Группа 1");  // Изменяем название группы
    ui->groupBox->adjustSize();          // Подгоняем размер под радиокнопки


    // ГРУППА 2
    ui->groupBox_2->setTitle("Группа 2");  // Изменяем название группы
    ui->comboBox->addItem("Значение 1");
    ui->comboBox->addItem("Значение 2");
    ui->comboBox->addItem("Значение 3");
    ui->comboBox->setCurrentIndex(1);

    ui->label->setText("Выпадающий список");

    ui->groupBox_2->adjustSize();          // Подгоняем размер
}

MainWindow::~MainWindow()
{
    delete ui;
}

