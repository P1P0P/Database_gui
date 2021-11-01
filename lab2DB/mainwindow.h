#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "initialization.h"
#include <QMainWindow>
#include <QtSql>
#include <QListWidget>
#include <QFile>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE
class initialization;
class MainWindow : public QMainWindow
{
    friend initialization;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();

private slots:
    void on_runButton_clicked();
    void on_delButton_clicked();
    void on_tablesList_itemDoubleClicked(QListWidgetItem *item);

private:
    QSqlDatabase m_db;
    QSqlQueryModel* m_model;
    QSqlQueryModel* m_model1;
    QFile file;
    QDateTime time1;
    Ui::MainWindow *ui;
    initialization* dialog;

};
#endif // MAINWINDOW_H
