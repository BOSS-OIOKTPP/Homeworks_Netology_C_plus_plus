#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    udpWorker = new UDPworker(this);
    udpWorker->InitSocket();

    connect(udpWorker, &UDPworker::sig_sendTimeToGUI, this, &MainWindow::DisplayTime);
    connect(udpWorker, &UDPworker::sig_sendUserMessageToGUI, this, &MainWindow::DisplayUserMessage);

    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [&]{

        QDateTime dateTime = QDateTime::currentDateTime();

        QByteArray dataToSend;
        QDataStream outStr(&dataToSend, QIODevice::WriteOnly);
        outStr << dateTime;

        udpWorker->SendDatagram(dataToSend);
    });

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_start_clicked()
{
    timer->start(TIMER_DELAY);
}


void MainWindow::DisplayTime(QDateTime data)
{
    counterPck++;
    if(counterPck % 20 == 0){
        ui->te_result->clear();
    }

    ui->te_result->append("Текущее время: " + data.toString() + ". "
                "Принято пакетов " + QString::number(counterPck));


}


void MainWindow::on_pb_stop_clicked()
{
    timer->stop();
}

void MainWindow::on_pb_sendDatagram_clicked()
{
    const QByteArray text = ui->le_message->text().toUtf8();
    if (!text.isEmpty()) {
        QByteArray packet;
        packet.append(kUserTextDatagramMarker);
        packet.append(text);
        udpWorker->SendDatagram(packet);
    }
}

void MainWindow::DisplayUserMessage(QString senderAddress, qint64 size)
{
    ui->te_result->append(QString("Принято сообщение от %1, размер сообщения(байт) %2")
                          .arg(senderAddress).arg(size));
}

