#ifndef FORM_VVOD_H
#define FORM_VVOD_H

#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QDateEdit>


#include<QDate>

namespace Ui {
class Form_vvod;
}

class Form_vvod : public QDialog
{
    Q_OBJECT

public:
    explicit Form_vvod(QSqlDatabase base_db,QWidget *parent = nullptr);
    ~Form_vvod();
QSqlDatabase base;
private slots:
    void on_pushButton_vvod_clicked();

    void on_pushButton_exit_clicked();

    void on_article_comboBox_currentIndexChanged(int index);

    void on_article_comboBox_num_currentIndexChanged(int index);

    void on_number_comboBox_currentIndexChanged(int index);

    void on_numberres_comboBox_currentIndexChanged(int index);

    void on_dateEdit_v_userDateChanged(const QDate &date);

private:
    Ui::Form_vvod *ui;
    QDate data_t;
    QSqlQueryModel *model_number, *model_article,*model_article1;
    QSqlQueryModel *model_prison, *model_prisonres;
    QSqlTableModel *model;
    int  Article_id_tmp,Prigovor_id_tmp,Stamp_id_tmp;
    bool FIND_FED_SEARCH, FIND_ARHIV;

};

#endif // FORM_VVOD_H
