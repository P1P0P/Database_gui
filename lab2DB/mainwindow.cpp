#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    dialog = new initialization(m_db);
    //dialog->show();
    if(!dialog->exec())
        exit(0);
    m_model = new QSqlQueryModel;
    ui->resultTable->setModel(m_model);
    ui->tablesList->addItems(m_db.tables());
    QSqlQuery myQ(m_db);
    myQ.exec("SELECT table_name FROM INFORMATION_SCHEMA.tables WHERE table_type='VIEW' AND table_schema=ANY(current_schemas(false)) ORDER BY table_name;");
    while(myQ.next())
    {
        QSqlRecord rec = myQ.record();
    for(int i = 0; i < rec.count(); i++)
    {
        ui->tablesList->addItem(rec.value(i).toString());
    }
    }
    file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);
    ui->logsTextBrowser->setText(file.readAll());

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_runButton_clicked()
{
    m_model->setQuery(ui->inputTextEdit->toPlainText());
    if(m_model->lastError().isValid()) {
       ui->errorsTextBrowser->setText("Error: " + m_model->lastError().text());
    }
    else
    {
        ui->errorsTextBrowser->setText("Success");
        time1 = QDateTime::currentDateTime();
        ui->logsTextBrowser->setText(ui->logsTextBrowser->toPlainText() + time1.toString("[dd.MM.yy , hh:mm:ss] -> ") + ui->inputTextEdit->toPlainText() + '\n');
        QTextStream out(&file);
        out << time1.toString("[dd.MM.yy , hh:mm:ss] -> ") + ui->inputTextEdit->toPlainText() + '\n';

    }
    ui->tablesList->clear();
    ui->tablesList->addItems(m_db.tables());
    QSqlQuery myQ(m_db);
    myQ.exec("SELECT table_name FROM INFORMATION_SCHEMA.tables WHERE table_type='VIEW' AND table_schema=ANY(current_schemas(false)) ORDER BY table_name;");


    while(myQ.next())
    {
        QSqlRecord rec = myQ.record();
    for(int i = 0; i < rec.count(); i++)
    {
        ui->tablesList->addItem(rec.value(i).toString());
    }}
    ui->inputTextEdit->setText("");
}

void MainWindow::on_delButton_clicked()
{
    file.remove();
    ui->logsTextBrowser->setText("");
    file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);
}

void MainWindow::on_tablesList_itemDoubleClicked(QListWidgetItem *item)
{
    m_model->setQuery("SELECT * FROM " + item->text());
    ui->errorsTextBrowser->clear();
}

QString MainWindow::getDbName(MainWindow &k)
{
    return k.m_db.databaseName();
}

