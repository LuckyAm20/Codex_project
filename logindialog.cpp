#include "logindialog.h"
#include "ui_logindialog.h"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");

       QString pathToDB = QDir::currentPath()+QString("/database/codex.sqlite");
       db.setDatabaseName(pathToDB);

       QFileInfo checkFile(pathToDB);

       if (checkFile.isFile()) {
           if (db.open()) {
               ui->result->setText("[+] Connected to Database File");
           }
           else {
               ui->result->setText("[!] Database File was not opened");
           }
       }
       else {
           ui->result->setText("[!] Database File does not exist");
       }

}

LoginDialog::~LoginDialog()
{
    delete ui;
    qDebug() << "Closing the connection to Database file on exist";
        db.close();
}

void LoginDialog::on_btnLogin_clicked()
{

    QString Username,Password;

    Username = ui->txtUser->text();
    Password = ui->txtPass->text();

    if (!db.isOpen()) {
        qDebug() << "No connection to Database";
        return;
    }

    QSqlQuery qry;

    if (qry.exec("SELECT name, password FROM users WHERE name=\'" + Username + "\' AND password=\'" + Password + "\'"))
    {
        if (qry.next()) {
            ui->result->setText("[+] Valid name and password");
            QString msg = "name = " + qry.value(0).toString() + "\n" +
                    "password = " + qry.value(1).toString() + "\n" ;
            LoginDialog::accept();
        }
        else {
           ui->result ->setText("[-] Wrong Username or Password");
        }
    }
    else {
        ui->result->setText("[-] Wrong query");
    }

}

void LoginDialog::on_btnClear_clicked()
{
    ui->txtUser->setText("");
     ui->txtPass->setText("");
     LoginDialog::reject();

}
