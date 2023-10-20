#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMenu>
#include <QMenuBar>
#include <QtGui>
#include <QtSql>
#include "articleform.h"
#include "form_vvod.h"
#include "articleform.h"
#include "dialogarhiv.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ArticleForm articleForm;
    ui->setupUi(this);
    db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("c:/qt/codeks.sqlite");
    if (db.open())
    {
            listmodel = new QSqlRelationalTableModel(this,db);
            listmodel->setTable("new_list");
            articleIndex = listmodel->fieldIndex("article");
            listmodel->setRelation(articleIndex, QSqlRelation("article", "id", "text"));

            numberIndex = listmodel->fieldIndex("number");
            listmodel->setRelation(numberIndex, QSqlRelation("type_prigovor", "id", "type"));

            listmodel->setHeaderData(NEW_LIST_FIO, Qt::Horizontal,
                                        tr(" ФАМИЛИЯ ИМЯ "));
            listmodel->setHeaderData(NEW_LIST_STAMP, Qt::Horizontal,
                                          tr("ОТПЕЧАТОК"));
            listmodel->setHeaderData(NEW_LIST_ARTICLE, Qt::Horizontal,
                                         tr("СТАТЬЯ"));
            listmodel->setHeaderData(NEW_LIST_NUMBER, Qt::Horizontal,
                                         tr(" Тип наказания"));
            listmodel->setHeaderData(NEW_LIST_DATAIN, Qt::Horizontal,
                                         tr(" Дата начала наказания"));
            listmodel->setHeaderData(NEW_LIST_DATAOUT, Qt::Horizontal,
                                         tr(" Дата окончания наказания"));

            listmodel->select();

            QSqlTableModel *tabModel = listmodel->relationModel(articleIndex);

                 ui->articleComboBox->setModel(tabModel);
                 ui->articleComboBox->setModelColumn(tabModel->fieldIndex("text"));


             QSqlTableModel *numbermodel = listmodel->relationModel(numberIndex);
             ui->numberComboBox->setModel(numbermodel);
             ui->numberComboBox->setModelColumn(numbermodel->fieldIndex("type"));

            mapper = new QDataWidgetMapper(this);
            mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
            mapper->setModel(listmodel);
            mapper->setItemDelegate(new QSqlRelationalDelegate(this));
            mapper->addMapping(ui->listLineEdit_fio,  NEW_LIST_FIO);
            mapper->addMapping(ui->listLineEdit_stamp, NEW_LIST_STAMP);
            mapper->addMapping(ui->listLineEdit_data, NEW_LIST_DATAIN);

            mapper->addMapping(ui->articleComboBox, articleIndex);
            mapper->addMapping(ui->numberComboBox, numberIndex);

            mapper->toFirst();



            ui->listtableView->setModel(listmodel);

            ui->listtableView->setSelectionMode(QAbstractItemView::SingleSelection);
            ui->listtableView->setSelectionBehavior(QAbstractItemView::SelectRows);
            ui->listtableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
            ui->listtableView->horizontalHeader()->setStretchLastSection(true);
            ui->listtableView->setColumnHidden(NEW_LIST_Id, true);
            ui->listtableView->setColumnWidth(1, 200 );
            ui->listtableView->setColumnWidth(2, 120 );
            ui->listtableView->setColumnWidth(3, 120 );
            ui->listtableView->setColumnWidth(4, 120 );
            ui->listtableView->setColumnWidth(5, 300 );
            ui->listtableView->setColumnWidth(6, 300 );
            ui->statusbar->showMessage("Вы подключились");
            date_str=QDate::currentDate().toString(Qt::ISODate);

            ui->TimelineEdit->setText(date_str);
    }
    else {
        ui->statusbar->showMessage("Вы не подключились");
    }
}

MainWindow::~MainWindow()
{
    delete ui;
    db.close();
}


void MainWindow::on_pushBVvod_clicked()
{
    if(Form_vvod(db).exec() == QDialog::Accepted)
        {

        listmodel->select();
        ui->listtableView->setModel(listmodel);

        }

}

void MainWindow::on_Arcticle_pushButton_clicked()
{
ArticleForm().exec();
}

void MainWindow::on_listtableView_activated(const QModelIndex &index)
{
    mapper->setCurrentModelIndex(index);
    listmodel->select();
}

void MainWindow::on_listtableView_clicked(const QModelIndex &index)
{
   mapper->setCurrentModelIndex(index);
   listmodel->select();
}

void MainWindow::on_pushButton_3_clicked()
{
    QMessageBox *msgBox = new QMessageBox(QMessageBox::Information," Закрыть день ","Данные будут перенесены.Вы уверены?",QMessageBox::Ok| QMessageBox::Cancel);

    if(msgBox->exec() == QMessageBox::Ok)
      {
      QSqlQuery query;
      query.prepare("INSERT INTO arhiv Select * From new_list");
      query.exec();
      query.prepare("DELETE  From new_list");
      query.exec();
      listmodel->select();
      }
      delete msgBox;
 }


void MainWindow::on_pushButton_2_clicked()
{
   Dialogarhiv(db).exec();
}

void MainWindow::on_Arcticle_pushButton_2_clicked()
{
    close();
    db.close();

}
