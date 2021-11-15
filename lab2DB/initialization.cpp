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
    file_conn.setFileName("Connections.txt");
    file_conn.open(QIODevice::ReadOnly);
    temp.setFileName("temp.txt");
    temp.open(QIODevice::Append);
}

initialization::~initialization()
{
    delete ui;
}

void initialization::on_pushButton_clicked()
{
    //проверка на заполнение
    if(ui->ip_Label->text() == "" || ui->password_Label->text() == ""|| ui->name_Label->text() == "" || ui->port_Label->text() == "" || ui->login_Label->text() == ""){
        ui->m_error->setText("Please, fill in all input fields");
    }
    else{
        //проверка на правильный ввод
        QTextStream out_temp(&temp);
        QTextStream out_conn(&file_conn);
        time2 = QDateTime::currentDateTime();

        bool flag_pass = false;
        bool new_user = true;

        QTextStream in(&file_conn);
        in.seek(0);
        QString line = in.readLine();
//      qint64 pos;
        while (!line.isNull()) {
            if(line == ui->login_Label->text()){
                new_user = false;
                //pos = in.pos();
                line = in.readLine();
                if(line == ui->password_Label->text()){
                    flag_pass = true;
                }
//              else {
//                  line = in.seek(pos);
//              }
            }
            line = in.readLine();
        }
        if(flag_pass == false && new_user == false)
            ui->m_error->setText("Incorrect login or password");
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

//                file_conn.close();
//                file_conn.open(QIODevice::Append);
//                out_conn<< time2.toString("[dd.MM.yy , hh:mm:ss] -> ")
//                            + ui->name_Label->text()     + '\n'
//                            + ui->ip_Label->text()       + '\n'
//                            + ui->port_Label->text()     + '\n'
//                            + ui->login_Label->text()    + '\n'
//                            + ui->password_Label->text() + '\n' + '\n';
            }

            if(m_db.isOpen())
                accept();
            else
                ui->m_error->setText(m_db.lastError().text());
            file_conn.close();
        }
    }
}
