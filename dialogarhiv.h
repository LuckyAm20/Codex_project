#ifndef DIALOGARHIV_H
#define DIALOGARHIV_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QTextDocument>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QObject>
#include <QSqlRelationalTableModel>
#include "dialog_dez.h"
#include <QModelIndex>
#include <QVariant>

class QPrinter;
class QSqlTableModel;

namespace Ui {
class Dialogarhiv;
}

class Dialogarhiv : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogarhiv(QSqlDatabase base_db,QWidget *parent = nullptr);
    ~Dialogarhiv();
    QSqlDatabase base1;
private slots:
   void on_pushButton_clicked();
   void on_pushButton_2_clicked();
   void on_pushButton_3_clicked();
   void on_pushButton_4_clicked();

   void on_pushButton_5_clicked();

   void on_dateE_out1_userDateChanged(const QDate &date);

   void on_dateE_in1_userDateChanged(const QDate &date);

private:
    Ui::Dialogarhiv *ui;
    QSqlRelationalTableModel *model_arh;
    QSqlQueryModel *model_view;
    void createU();
    QVariant myData;
    QModelIndex myIndex;
    int articleIndex, numberIndex;
};

#endif // DIALOGARHIV_H
