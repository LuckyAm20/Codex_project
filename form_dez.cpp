#include "form_dez.h"
#include "ui_form.h"


Form_dez::Form_dez(QString str1, QWidget *parent) : QWidget(parent), ui(new Ui::Form_dez)
{
  ui->str_in->setText(str1);
    ui->setupUi(this);
}

Form_dez::~Form_dez()
{
    delete ui;
}
