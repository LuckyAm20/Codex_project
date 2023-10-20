#ifndef FORM_H
#define FORM_H

#include <QWidget>
#include <QString>

namespace Ui {
class Form_dez ;
}

class Form_dez : public QWidget
{
    Q_OBJECT

public:
     Form_dez(QString str1, QWidget *parent = nullptr);
    ~Form_dez();
    QString str1;
private:
    Ui::Form_dez *ui;
};

#endif // FORM_H
