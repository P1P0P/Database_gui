#include "initialization.h"
#include "ui_initialization.h"
#include <QFile>
#include <QSettings>

initialization::initialization(QSqlDatabase& db) :
    QDialog(),
    m_db(db),
    ui(new Ui::initialization)
{
    ui->setupUi(this);
    temp.setFileName("temp.txt");
    temp.open(QIODevice::ReadWrite);
    QSettings settings;
    settings.beginGroup("/Database_browser/settings");
    ui->name_Label->setText     (settings.value("Database_name", "fn1131_2021" ).toString());
    ui->ip_Label->setText       (settings.value("Host_ip"      , "195.19.32.74").toString());
    ui->port_Label->setText     (settings.value("P0rt"         , 5432          ).toString());
    ui->login_Label->setText    (settings.value("L0g1n"        , "student"     ).toString());
    ui->password_Label->setText (settings.value("Password"     , "bmstu"       ).toString());
    settings.sync();
    settings.endGroup();
}

initialization::~initialization()
{
    delete ui;
}

void initialization::on_pushButton_clicked()
{
    //проверка на заполнение
    if(ui->ip_Label->text() == "" || ui->password_Label->text() == ""|| ui->name_Label->text() == "" || ui->port_Label->text() == "" || ui->login_Label->text() == "")
        ui->m_error->setText("Please, fill in all input fields");
    else{
        m_db.setDatabaseName(ui->name_Label->text());
        m_db.setHostName(ui->ip_Label->text());
        m_db.setPassword(ui->password_Label->text());
        m_db.setPort(ui->port_Label->text().toInt());
        m_db.setUserName(ui->login_Label->text());
        if(m_db.open()){
            QSettings settings;
            settings.beginGroup("/Database_browser/settings");
            settings.setValue("Database_name", ui->name_Label->text()    );
            settings.setValue("Host_ip"      , ui->ip_Label->text()      );
            settings.setValue("P0rt"         , ui->port_Label->text()    );
            settings.setValue("L0g1n"        , ui->login_Label->text()   );
            settings.setValue("Password"     , ui->password_Label->text());
            settings.sync();
            settings.endGroup();
        }

        if(m_db.isOpen())
            accept();
        else
            ui->m_error->setText(m_db.lastError().text());

    }

}

