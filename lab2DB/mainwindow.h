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
    friend class initialization;
    Q_OBJECT

public:
    MainWindow(QWidget *parent = NULL);
    ~MainWindow();
    QString getDbName(MainWindow&);

private slots:
    void on_runButton_clicked();
    void on_delButton_clicked();
    void on_tablesList_itemDoubleClicked(QListWidgetItem *item);

    void on_action_triggered();

private:
    QSqlDatabase m_db;
    QSqlQueryModel* m_model;
    QFile file;
    QDateTime time1;
    Ui::MainWindow *ui;
    initialization* dialog;
    void update_table_list();
};
#endif // MAINWINDOW_H
