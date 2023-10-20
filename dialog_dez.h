#ifndef DIALOG_DEZ_H
#define DIALOG_DEZ_H

#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QVariantList>
#include <QTableWidgetItem>

namespace Ui {
class Dialog_dez;
}

class Dialog_dez : public QDialog
{
    Q_OBJECT

public:
  explicit Dialog_dez(const QString str1,QVariantList dat, int numer_stlb, int number_culb ,QString strdata,QString strdata1,QWidget *parent = nullptr);
    ~Dialog_dez();
    QString str1;
    QLineEdit   *lineEdit;

private slots:

    void on_buttonBox_accepted();

private:
    Ui::Dialog_dez *ui;
    QString str_sezon;


};

#endif // DIALOG_DEZ_H
