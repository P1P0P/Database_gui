#include "initialization.h"
#include "ui_initialization.h"


initialization::initialization(QSqlDatabase& db) :
    QDialog(),
    ui(new Ui::initialization),
    m_db(db)
{
    ui->setupUi(this);
    file_conn.setFileName("Connections.txt");
    file_conn.open(QIODevice::Append);
}

initialization::~initialization()
{
    delete ui;
}

void initialization::on_pushButton_clicked()
{
    if(ui->ip_Label->text() == "" || ui->password_Label->text() == ""|| ui->name_Label->text() == "" || ui->port_Label->text() == "" || ui->login_Label->text() == ""){
        ui->m_error->setText("Please, fill in all input fields");
    }
    else{
    time2 = QDateTime::currentDateTime();
    m_db.setDatabaseName(ui->name_Label->text());
    m_db.setHostName(ui->ip_Label->text());
    m_db.setPassword(ui->password_Label->text());
    m_db.setPort(ui->port_Label->text().toInt());
    m_db.setUserName(ui->login_Label->text());

    QTextStream in(&file_conn);
    QString line = in.readLine();
//    while (!line.isNull()) {
//            process_line(line);
//            line = in.readLine();
//        }

    QTextStream out_conn(&file_conn);

    out_conn<< time2.toString("[dd.MM.yy , hh:mm:ss] -> ")
               + ui->name_Label->text() + '\n'
               + ui->ip_Label->text() + '\n'
               + ui->port_Label->text() + '\n'
               + ui->login_Label->text() + '\n'
               + ui->password_Label->text() + '\n' + '\n';


    if(m_db.open())
        accept();
    else
        ui->m_error->setText(m_db.lastError().text());
    }
}
