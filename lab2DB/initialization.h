#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mainwindow.h"
#include <QWidget>
#include <QDialog>
#include <QSqlDatabase>
#include <QFile>
#include <QDateTime>

namespace Ui {
class initialization;
}

class initialization : public QDialog
{
    friend class MainWindow;
    Q_OBJECT

public:
    explicit initialization(QSqlDatabase& db);
    ~initialization();


private slots:
    void on_pushButton_clicked();

private:
    QSqlDatabase& m_db;
    Ui::initialization *ui;
    QFile temp;
    QDateTime time2;
};

#endif // INITIALIZATION_H
