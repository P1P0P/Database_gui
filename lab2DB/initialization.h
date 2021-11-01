#ifndef INITIALIZATION_H
#define INITIALIZATION_H
#include "mainwindow.h"
#include <QWidget>
#include <QDialog>
#include <QSqlDatabase>

namespace Ui {
class initialization;
}

class initialization : public QDialog
{
    Q_OBJECT

public:
    explicit initialization(QSqlDatabase& db);
    ~initialization();

private slots:
    void on_pushButton_clicked();

private:
    QSqlDatabase& m_db;
    Ui::initialization *ui;
};

#endif // INITIALIZATION_H
