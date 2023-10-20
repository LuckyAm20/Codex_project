 #include "dialogarhiv.h"
#include "ui_dialogarhiv.h"
#include "dialog_dez.h"


Dialogarhiv::Dialogarhiv(QSqlDatabase base_db,QWidget *parent) : QDialog(parent), ui(new Ui::Dialogarhiv)
{
    ui->setupUi(this);
    this->createU();
    ui->rB_z->setChecked(true);
    ui->dateEdit_G->setDisplayFormat("yyyy");
    ui->dateEdit_G->setDate (QDate::currentDate());
    ui->dateEdit_G2->setDisplayFormat("yyyy-MM");
    ui->dateEdit_G2->setDate (QDate::currentDate());
    ui->dateEdit_SVO->setDate (QDate::currentDate());
    base1= base_db;
    model_arh=new QSqlRelationalTableModel(this,base1);
    model_arh->setTable("arhiv");
    articleIndex = model_arh->fieldIndex("article");
    model_arh->setRelation(articleIndex, QSqlRelation("article", "id", "text"));

    numberIndex = model_arh->fieldIndex("number");
    model_arh->setRelation(numberIndex, QSqlRelation("type_prigovor", "id", "type"));

    model_arh->setHeaderData(1, Qt::Horizontal,
                                tr(" ФАМИЛИЯ ИМЯ "));
    model_arh->setHeaderData(2, Qt::Horizontal,
                                  tr("ОТПЕЧАТОК"));
    model_arh->setHeaderData(3, Qt::Horizontal,
                                 tr("СТАТЬЯ"));
    model_arh->setHeaderData(4, Qt::Horizontal,
                                 tr(" Тип наказания"));
    model_arh->setHeaderData(5, Qt::Horizontal,
                                 tr(" Дата начала наказания"));
    model_arh->setHeaderData(6, Qt::Horizontal,
                                 tr(" Дата окончания наказания"));

    model_arh->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model_arh->select();

    ui->tableView_arh-> setEditTriggers(QAbstractItemView::NoEditTriggers); // запрет редактирования таблицы
    ui->tableView_arh ->setModel(model_arh);
}

Dialogarhiv::~Dialogarhiv()
{
    delete ui;
}
void Dialogarhiv::createU()
{
ui->dateE_in->setDate(QDate::currentDate());
ui->dateE_out->setDate(QDate::currentDate());
ui->dateE_in1->setDate(QDate::currentDate());
ui->dateE_out1->setDate(QDate::currentDate());
}


void Dialogarhiv::on_pushButton_clicked()
{
if ((ui->fio_lineEdit->text().length()>=1) and(ui->lineEdit->text().length()>=1))
model_arh->setFilter(QString("(fio LIKE '%%1%' OR stamp = '%4') AND datain between '%2' and '%3'").arg( ui->fio_lineEdit->text(),ui->dateE_in->date().toString("yyyy-MM-dd"),ui->dateE_out->date().toString("yyyy-MM-dd"),ui->lineEdit->text()));
else model_arh->setFilter(QString("datain between '%1' and '%2'").arg(ui->dateE_in->date().toString("yyyy-MM-dd"),ui->dateE_out->date().toString("yyyy-MM-dd")));
}

void Dialogarhiv::on_pushButton_2_clicked()
{
    QString qqqq=ui->dateEdit_G2->date().toString("MM");
    QSqlQueryModel * model_view = new QSqlQueryModel();
    QSqlQuery qry2;
    qry2.prepare(" SELECT strftime('%m',datain) as 'Месяц ', count(article)*100/ ( SELECT count(*) from arhiv WHERE strftime('%m', datain)=:yers) as '%  записей',article.nomer as 'Номер статьи', article.text as '  Содержание статьи ' FROM arhiv, article WHERE arhiv.article=article.id AND  strftime('%m', datain)=:yers GROUP BY  strftime('%m',datain), article ORDER BY  count(article)*100/ ( SELECT count(*) from arhiv WHERE strftime('%m', datain)=:yers) DESC;");
    qry2.bindValue(":yers",ui->dateEdit_G2->date().toString("MM"));
    qry2.exec();
    model_view->setQuery(qry2);
    ui->tableView_q ->setModel(model_view);
    ui->tableView_q->show();


}


void Dialogarhiv::on_pushButton_3_clicked()
{

          QSqlQueryModel * model_view = new QSqlQueryModel();
          QSqlQuery qry2;
          qry2.prepare(" SELECT strftime('%Y',datain) as ' Год  ', count(article)*100/ ( SELECT count(*) from arhiv WHERE strftime('%Y', datain)=:yers) as '%  записей',article.nomer as 'Номер статьи',article.text as '  Содержание статьи ' FROM arhiv, article WHERE arhiv.article=article.id AND  strftime('%Y', datain)=:yers GROUP BY  strftime('%Y',datain), article ORDER BY count(article)*100/ ( SELECT count(*) from arhiv WHERE strftime('%Y', datain)=:yers) DESC;");
          qry2.bindValue(":yers",ui->dateEdit_G->date().toString("yyyy"));
          qry2.exec();
          model_view->setQuery(qry2);
          ui->tableView_q ->setModel(model_view);
          ui->tableView_q->show();

}

void Dialogarhiv::on_pushButton_4_clicked()
{
    QDate dateN,dateQ;
    QString tmp_str;

    if (ui->rB_z->isChecked()) {
    dateN = ui->dateE_in1->date();
    dateN.setDate((ui->dateE_in1->date().year()-1),12,1);
    dateQ = ui->dateE_out1->date();
    dateQ.setDate(ui->dateE_out1->date().year(),2,1);
    QString temp1=dateN.toString("yyyy-MM");
    tmp_str="зима";
     }
    if (ui->rB_v->isChecked()) {
    dateN = ui->dateE_in1->date();
    dateN.setDate(ui->dateE_in1->date().year(),3,1);
    dateQ = ui->dateE_out1->date();
    dateQ.setDate(ui->dateE_out1->date().year(),5,1);
    QString temp1=dateN.toString("yyyy-MM");
    tmp_str="весна";
     }

    if (ui->rB_l->isChecked()) {
    dateN = ui->dateE_in1->date();
    dateN.setDate(ui->dateE_in1->date().year(),6,1);
    dateQ = ui->dateE_out1->date();
    dateQ.setDate(ui->dateE_out1->date().year(),8,1);
    QString temp1=dateN.toString("yyyy-MM");
    tmp_str="лето";
     }
    if (ui->rB_o->isChecked()) {
    dateN = ui->dateE_in1->date();
    dateN.setDate(ui->dateE_in1->date().year(),9,1);
    dateQ = ui->dateE_out1->date();
    dateQ.setDate(ui->dateE_out1->date().year(),11,1);
    QString temp1=dateN.toString("yyyy-MM");
    tmp_str="осень";
     }
    QSqlQueryModel * model_view = new QSqlQueryModel();
    QSqlQuery qry2;
    qry2.prepare(" SELECT count(article)*100/(SELECT count(*) from arhiv WHERE strftime('%Y-%m',datain)BETWEEN :yers AND :yers1) as '%  записей', article.nomer as 'Номер статьи', article.text as 'Содержание статьи' FROM arhiv, article WHERE arhiv.article=article.id AND strftime('%Y-%m',datain) BETWEEN :yers AND :yers1 GROUP BY article ORDER BY count(article)*100/ ( SELECT count(*) from arhiv WHERE strftime('%Y', datain)BETWEEN :yers AND :yers1) DESC;");
    qry2.bindValue(":yers",dateN.toString("yyyy-MM"));
    qry2.bindValue(":yers1",dateQ.toString("yyyy-MM"));
    qry2.exec();
    model_view->setQuery(qry2);
    ui->tableView_q ->setModel(model_view);
    ui->tableView_q->show();

    QVariantList data;
       for (int i = 0; i < ui->tableView_q->model()->rowCount(); ++i) {
        QSqlRecord record =model_view->record(i);
        data.append(record.value("%  записей").toString());
        data.append(record.value("Номер статьи").toString());
        data.append(record.value("Содержание статьи").toString());
    }
      int  numer_stlb=ui->tableView_q->model()->columnCount();
      int  number_culb= ui->tableView_q->model()->rowCount();
      QDate dataStr=ui->dateE_in1->date();
      QDate dataStr1=ui->dateE_out1->date();
      QString strdata=dataStr.toString("yyyy");
      QString strdata1=dataStr1.toString("yyyy");
      Dialog_dez  my_dez(tmp_str,data,numer_stlb,number_culb, strdata,strdata1);
      my_dez.exec();
}


void Dialogarhiv::on_pushButton_5_clicked()
{
    QDate dateN1;
    dateN1 = ui->dateEdit_SVO->date();

    QSqlQueryModel * model_view = new QSqlQueryModel();
    QSqlQuery qry2;
    qry2.prepare("SELECT arhiv.fio as 'Фамилия Имя Отчество',arhiv.stamp as 'Отпечаток', article.text as ' Содержание статьи' FROM arhiv,article WHERE arhiv.article=article.id AND  strftime('%Y-%m',dataout)<=:yers AND (arhiv.number=1 OR arhiv.number=4)  ");
    qry2.bindValue(":yers",dateN1.toString("yyyy-MM"));
    qry2.exec();
    model_view->setQuery(qry2);
    ui->tableView_q ->setModel(model_view);
    ui->tableView_q->show();

}
