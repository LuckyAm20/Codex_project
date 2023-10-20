#include "dialog_dez.h"
#include "ui_dialog_dez.h"

Dialog_dez::Dialog_dez( QString str1,QVariantList dat,int numer_stlb,int number_culb, QString strdata,QString strdata1, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_dez)
{


    ui->setupUi(this);
    ui->lineEdit_data->setText(strdata);
    ui->lineEdit_data_2->setText(strdata1);
    ui->lineEdit_sez->setText(str1);
    QStringList horzHeaders;
      horzHeaders << "% Записей" << " Номер статьи " << "Содержание статьи";
      ui->tableW->setHorizontalHeaderLabels(horzHeaders);
      ui->tableW->setRowCount(number_culb);
      ui->tableW->setColumnCount( numer_stlb);


   for(int stroka = 0; stroka <number_culb; stroka++){
       int rez= numer_stlb*stroka;
     for ( int column = 0; column < numer_stlb; ++column ) {
        ui->tableW->setItem(stroka, column, new QTableWidgetItem(dat[column+rez].toString()));
    }
   }



}

Dialog_dez::~Dialog_dez()
{
    delete ui;
}


void Dialog_dez::on_buttonBox_accepted()
{
    close();
}
