#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "stopwatch.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private slots:

    void updateTimeDisplay(qint64 elapsedMs);    
    void on_startStopButton_clicked();
    void on_lapButton_clicked();
    void on_resetButton_clicked();

private:
    void setupUI();

    QString formatTime(qint64 ms) const;

    // Секундомер
    Stopwatch *_stopwatch;


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
