#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Создаём экземпляр секундомера
    _stopwatch = new Stopwatch(this);

    // Подключаем сигнал секундомера к слоту главного окна
    connect(_stopwatch, &Stopwatch::timeUpdated, this, &MainWindow::updateTimeDisplay);    

    // Кнопка Круг изначально неактивна
    ui->lapButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startStopButton_clicked()
{
    // если секундомер работает, то останавливаем
    if (_stopwatch->isRunning()) {
        _stopwatch->stop();
        ui->startStopButton->setText("Старт");
        ui->lapButton->setEnabled(false);
    }
    // иначе запускаем
    else {
        _stopwatch->start();
        ui->startStopButton->setText("Стоп");
        ui->lapButton->setEnabled(true);
    }
}

void MainWindow::on_lapButton_clicked()
{
    _stopwatch->lap();

    int lapNumber = _stopwatch->getLapCount();     // Количество кругов
    const auto& laps = _stopwatch->getLapTimes();  // Ссылка на список
    if (!laps.isEmpty()) {
        qint64 lapTimeMs = laps.last();            // Прочитали время в миллисекундах
        double seconds = lapTimeMs / 1000.0;       // Перевели в секунды
        QString lapText = QString("Круг %1, время: %2 сек")
                             .arg(lapNumber)
                             .arg(seconds, 0, 'f', 1);
        ui->lapsBrowser->append(lapText);
    }
}

void MainWindow::on_resetButton_clicked()
{
    _stopwatch->reset();

    ui->timeLabel->setText("0.0 сек");
    ui->lapsBrowser->clear();
    ui->startStopButton->setText("Старт");
    ui->lapButton->setEnabled(false);
}

void MainWindow::updateTimeDisplay(qint64 elapsedMs)
{
    double seconds = elapsedMs / 1000.0;
    ui->timeLabel->setText(QString("%1 сек").arg(seconds, 0, 'f', 1));
}

