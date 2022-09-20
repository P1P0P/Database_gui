#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDateTime>
#include <iostream>
#include <QtSql>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    m_db = QSqlDatabase::addDatabase("QPSQL");
    dialog = new initialization(m_db);

    QSettings settings;
    settings.beginGroup("/Database_browser/settings");
    m_db.setDatabaseName(settings.value("Database_name", "fn1131_2021" ).toString());
    m_db.setHostName    (settings.value("Host_ip"      , "195.19.32.74").toString());
    m_db.setPort        (settings.value("P0rt"         , 5432          ).toInt()   );
    m_db.setUserName    (settings.value("L0g1n"        , "student"     ).toString());
    m_db.setPassword    (settings.value("Password"     , "bmstu"       ).toString());
    settings.endGroup();

    if (!m_db.open())
        ui->errorsTextBrowser->setText("Error: " + m_db.lastError().text());
    m_model = new QSqlQueryModel;
    ui->resultTable->setModel(m_model);
    update_table_list();


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
    update_table_list();

    QSqlQuery myQ(m_db);
    myQ.exec("SELECT table_name FROM INFORMATION_SCHEMA.tables WHERE table_type='VIEW' AND table_schema=ANY(current_schemas(false)) ORDER BY table_name;");

    /*while(myQ.next())
    {
        QSqlRecord rec = myQ.record();
    for(int i = 0; i < rec.count(); i++)
    {
        ui->tablesList->addItem(rec.value(i).toString());
    }}*/
    ui->inputTextEdit->setText("");
}

void MainWindow::on_delButton_clicked()
{
    file.remove();
    ui->logsTextBrowser->setText("");
    file.setFileName("logs.txt");
    file.open(QIODevice::ReadWrite);/*

    std::string query = "INSERT INTO cinema VALUES ";
    std::vector<std::string> names{"Мария Гусева", "Максим Свиридов", "Полина Парфенова", "Георгий Сахаров", "Сафия Тарасова",
                                       "Лука Герасимов", "Давид Кириллов", "Даниил Никитин", "Алина Окулова", "Михаил Масленников",
                                       "Анна Борисова", "Мария Макеева", "Роман Алексеев", "Егор Окулов", "Фёдор Корнилов",
                                       "Антон Макеев", "Валерия Герасимова", "Кирилл Некрасов", "Виктория Свиридова", "Алиса Новикова"};
    std::vector<std::string> films{"Славные парни", "Черный ястреб", "Старикам тут не место", "Десять негритят", "Хикарио",
                                      "Невидимый кулак", "Последние девушки", "Ловец снов", "Проклятие монахини", "Крепкий орешек 2",
                                      "21 и больше", "Карты, деньги, 2 стола", "Большой Куш", "По соображениям совести", "Взвод"};
    std::string name;
    std::string film;
    QDate date(2022, 01, 01);
    QTime time(7, 0, 0);
    int idn;
    for (int day = 0; day < (365 * 9); day++){
        for (int i = 0; i < 15 - i; i++){
            film = films[rand() % 15];
            for (int j = 0; j < (rand() % 20); j++){
                idn = rand() % (20 - j);
                name = names[idn];
                query += "('" + film + "', '" + (date.addDays(day)).toString("MM.dd.yyyy").toStdString() + "', '"
                        + (time.addSecs(i * 3600)).toString("hh:mm:ss").toStdString() + "', '" + name + "'), ";
                //m_model->setQuery(query.c_str());
                names.erase(names.begin() + idn);
                //qDebug() << query.c_str();
            }

            names = {"Мария Гусева", "Максим Свиридов", "Полина Парфенова", "Георгий Сахаров", "Сафия Тарасова",
                                                   "Лука Герасимов", "Давид Кириллов", "Даниил Никитин", "Алина Окулова", "Михаил Масленников",
                                                   "Анна Борисова", "Мария Макеева", "Роман Алексеев", "Егор Окулов", "Фёдор Корнилов",
                                                   "Антон Макеев", "Валерия Герасимова", "Кирилл Некрасов", "Виктория Свиридова", "Алиса Новикова"};
        }
    }
    query.pop_back();
    query.pop_back();
    m_model->setQuery(query.c_str());*/
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

void MainWindow::on_action_triggered()
{
    if (dialog->exec() == QDialog::Accepted){
        update_table_list();
        m_model->clear();
        setWindowTitle(getDbName(*this));
    }
}

void MainWindow::update_table_list()
{
    ui->tablesList->clear();
    ui->tablesList->addItems(m_db.tables());
}



