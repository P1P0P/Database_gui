#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow k;
    k.setWindowTitle(k.getDbName(k));
    k.show();



    return a.exec();
}
