#include "initialization.h"
#include "ui_initialization.h"


initialization::initialization(QSqlDatabase& db) :
    QDialog(),
    m_db(db),
    ui(new Ui::initialization)

{
    ui->setupUi(this);

}

initialization::~initialization()
{
    delete ui;
}

void initialization::on_pushButton_clicked()
{
    m_db.setDatabaseName(ui->name_Label->text());
    m_db.setHostName(ui->ip_Label->text());
    m_db.setPassword(ui->password_Label->text());
    m_db.setPort(ui->port_Label->text().toInt());
    m_db.setUserName(ui->login_Label->text());
    if(m_db.open())
        accept();
    else
        ui->m_error->setText(m_db.lastError().text());
}
