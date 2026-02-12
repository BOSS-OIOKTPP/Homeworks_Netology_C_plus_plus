#include "connectdb.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ConnectDB w;
    w.show();
    return a.exec();
}
