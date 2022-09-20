#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QApplication::setOrganizationName("ORGANIZATION_NAME");
    QApplication::setOrganizationDomain("ORGANIZATION_DOMAIN");
    QApplication::setApplicationName("APPLICATION_NAME");
    MainWindow k;
    k.setWindowTitle(k.getDbName(k));
    k.show();



    return a.exec();
}
