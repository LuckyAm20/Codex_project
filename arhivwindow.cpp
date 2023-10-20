#include "arhivwindow.h"
#include "ui_arhivwindow.h"

arhivWindow::arhivWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::arhivWindow)
{
    ui->setupUi(this);
    QSqlQueryModel * model_arh = new QSqlQueryModel();
    QSqlQuery * query_number = new QSqlQuery("Select * from arhiv");
     query_number->exec();
     model_arh->setQuery(*query_number);
}

arhivWindow::~arhivWindow()
{
    delete ui;
}
