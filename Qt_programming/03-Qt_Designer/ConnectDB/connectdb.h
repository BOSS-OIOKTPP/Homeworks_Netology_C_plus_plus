#ifndef CONNECTDB_H
#define CONNECTDB_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class ConnectDB; }
QT_END_NAMESPACE

class ConnectDB : public QMainWindow
{
    Q_OBJECT

public:
    ConnectDB(QWidget *parent = nullptr);
    ~ConnectDB();

private:
    Ui::ConnectDB *ui;
};
#endif // CONNECTDB_H
