#ifndef ARTICLEFORM_H
#define ARTICLEFORM_H

#include <QDialog>
#include <QDebug>
#include <QString>
#include <QSqlRecord>
#include <QTextDocument>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlRelationalTableModel>
#include <QMessageBox>
#include <QPainter>
#include <QPrinter>
#include <QPrintDialog>
#include <QPrintPreviewDialog>
#include <QObject>


#define ARTICLE_NOMER "nomer"
#define ARTICLE_TEXT  "text"

class QPrinter;
namespace Ui {
class ArticleForm;
}

class ArticleForm : public QDialog

{
    Q_OBJECT

public:
    explicit ArticleForm(QWidget *parent = nullptr);
    ~ArticleForm();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_released();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_art_comboBox_currentIndexChanged(int index);
    void on_artnum_comboBox_currentIndexChanged(int index);
    void on_srok_comboBox_currentIndexChanged(int index);
    void on_res_comboBox_currentIndexChanged(int index);
    void on_pushButton_5_clicked();

private:
    Ui::ArticleForm *ui;
    QSqlTableModel *modelarticle;
     QSqlRelationalTableModel *modelfed;
     QSqlQueryModel  *model_art,*model_artnum,*model_srok,*model_res;
     int articleInd, numberInd;
     void print();
     void PrintTable( QPrinter* printer,QSqlQuery&  Query);
};

#endif // ARTICLEFORM_H
