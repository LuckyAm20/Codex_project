#include "form_vvod.h"
#include "ui_form_vvod.h"

#include<QDebug>
#include<QMessageBox>



Form_vvod::Form_vvod(QSqlDatabase base_db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Form_vvod)
{
    ui->setupUi(this);

    FIND_FED_SEARCH= false;
    FIND_ARHIV=false;
    ui->dateEdit_v->setDisplayFormat("yyyy-MM-dd");
    ui->dateEdit_v->setDate (QDate::currentDate());
    data_t=ui->dateEdit_v->date();

    base= base_db;
    model = new QSqlTableModel(this);
    model->setTable("new_list");
    model->setHeaderData(1, Qt::Horizontal,
                                tr(" ФАМИЛИЯ ИМЯ "));
    model->setHeaderData(2, Qt::Horizontal,
                                  tr("ОТПЕЧАТОК"));
    model->setHeaderData(3, Qt::Horizontal,
                                 tr("СТАТЬЯ"));

    model->setHeaderData(4, Qt::Horizontal,
                                 tr(" Тип наказания"));
    model->setHeaderData(5, Qt::Horizontal,
                                 tr(" Дата начала наказания"));
    model->setHeaderData(6, Qt::Horizontal,
                                 tr(" Дата окончания наказания"));



    ui->tableView->setModel(model);
    model->select();

    QSqlQueryModel * model_number = new QSqlQueryModel();
    QSqlQuery * query_number = new QSqlQuery("Select type from type_prigovor");
     query_number->exec();
     model_number->setQuery(*query_number);
     ui->prigovor_comboBox->setModel(model_number);

     QSqlQueryModel * model_article = new QSqlQueryModel();
     QSqlQuery * query_article = new QSqlQuery("Select nomer from article");
      query_article->exec();
      model_article->setQuery(*query_article);
      ui->article_comboBox->setModel(model_article);

      QSqlQueryModel * model_article1 = new QSqlQueryModel();
      QSqlQuery * query_article1= new QSqlQuery("Select text from article");
       query_article1->exec();
       model_article1->setQuery(*query_article1);
      ui->article_comboBox_num->setModel(model_article1);

      QSqlQueryModel * model_prison = new QSqlQueryModel();
      QSqlQuery * query_prison= new QSqlQuery("Select prison_term from article");
       query_prison->exec();
       model_prison->setQuery(*query_prison);
       ui->number_comboBox->setModel(model_prison);

      QSqlQueryModel * model_prisonres = new QSqlQueryModel();
      QSqlQuery * query_prisonres= new QSqlQuery("Select prison_term_res from article");
       query_prisonres->exec();
       model_prisonres->setQuery(*query_prisonres);
      ui->numberres_comboBox->setModel(model_prisonres);



}

Form_vvod::~Form_vvod()
{
    delete ui;
}

void Form_vvod::on_pushButton_vvod_clicked()
{
    QString fio_tmp;
    int Article_id,Prigovor_id,Stamp_id,Article_srok;

     QString Article_txt,Prigovor_txt, Stamp_txt;
     int SROK_PLUS=0;

    fio_tmp=ui->fio_vvod->text();
    if (!base.isOpen()) {
        qDebug() << "No connection to Database";
        return;
    }

 if ((ui->fio_vvod->displayText().isEmpty() )||(ui->stamp_vvod->text().isEmpty()) )
 {
     QString msg = "Есть незаполненные поля!";
     QMessageBox::warning(this, "Ввод данных",msg);
     return;
 }

    Article_txt=ui->article_comboBox->currentText();
    Prigovor_txt=ui->prigovor_comboBox->currentText();
    Stamp_txt=ui->stamp_vvod->text();

    QSqlQuery qry(base);

    if (qry.exec("SELECT id,prison_term FROM article WHERE nomer=\'" + Article_txt +"\'"))
    {
        if (qry.next()) {
            Article_id=qry.value(0).toInt();
            Article_srok=qry.value(1).toInt();
            SROK_PLUS=Article_srok;
        }
    }

    if (qry.exec("SELECT id FROM type_prigovor WHERE type=\'" +Prigovor_txt +"\'"))
    {
        if (qry.next()) {
            Prigovor_id=qry.value(0).toInt();

        }
    }


    QSqlQuery qry2(base);

      if (qry2.exec("SELECT arhiv.id, arhiv.stamp , arhiv.dataout , article.prison_term,article.prison_term_res FROM arhiv, article WHERE arhiv.article=article.id AND stamp=\'" + Stamp_txt + "\' AND dataout >= \'" + ui->dateEdit_v->text() + "\'"))
      {
        if (qry2.next()) {
            Stamp_id=qry2.value(0).toInt();
            QDate arh_tmp=qry2.value(2).toDate();

             qint64 ttt=arh_tmp.toJulianDay();
             qint64 tetet=ui-> dateEdit_v->date().toJulianDay();
             qint64 rez=ttt-tetet;

            int tmp_1 = arh_tmp.year();
            int tmp_2 = ui-> dateEdit_v->date().year();
            SROK_PLUS=SROK_PLUS+(tmp_1-tmp_2);

            QSqlQuery query(base);
            query.prepare("UPDATE arhiv SET dataout= :idate where id = :myRow");
            query.bindValue(":idate",ui->dateEdit_v->text());
            query.bindValue(":myRow", Stamp_id);
            query.exec();
        }
    }
          QSqlQuery qry1(base);
          int  Article_id_tmp,Prigovor_id_tmp,Stamp_id_tmp, srok_tmp;
          if (qry1.exec("SELECT fed_search.id,fed_search.stamp,article.prison_term,article.prison_term_res FROM fed_search ,article  WHERE fed_search.article = article.id AND stamp=\'" + Stamp_txt +"\'"))
        {
            if (qry1.next()) {
                Article_id_tmp=qry1.value(2).toInt();
                Stamp_id_tmp=qry1.value(1).toInt();
                Prigovor_id_tmp=4;
                srok_tmp=qry1.value(3).toInt()+Article_srok;
                QSqlQuery qry12;
                qry12.prepare("DELETE  From fed_search WHERE stamp=\'" +Stamp_txt +"\'");
                qry12.exec();
                QSqlQuery query;
                query.prepare("INSERT INTO new_list (fio,stamp,article,number,datain,dataout)"
                        "VALUES( :fio_v, :stamp_v,:article_v,:number_v,:dt1,:dt)");
               query.bindValue( ":fio_v", ui->fio_vvod->text() );
               query.bindValue( ":stamp_v", Stamp_id_tmp);
               query.bindValue( ":article_v", Article_id_tmp);
               query.bindValue( ":number_v", Prigovor_id_tmp);
               query.bindValue( ":dt1",ui->dateEdit_v->text());
               query.bindValue( ":dt",data_t.addYears(srok_tmp));

               query.exec();
               model->select();
               accept();
            }
         }






    if ((ui->prigovor_comboBox->currentText()=="штраф")||ui->prigovor_comboBox->currentText()=="расстрел") SROK_PLUS=0;

    QSqlQuery query;

    query.prepare("INSERT INTO new_list (fio,stamp,article,number,datain,dataout)"
                "VALUES( :fio_v, :stamp_v,:article_v,:number_v,:dt1,:dt)" );
    query.bindValue( ":fio_v", ui->fio_vvod->text() );
    query.bindValue( ":stamp_v", ui->stamp_vvod->text().toInt());
    query.bindValue( ":article_v", Article_id);
    query.bindValue( ":number_v", Prigovor_id);
    query.bindValue( ":dt1",ui->dateEdit_v->text());
    query.bindValue( ":dt",data_t.addYears(SROK_PLUS));


    query.exec();
    model->select();
    accept();
}

void Form_vvod::on_pushButton_exit_clicked()
{
 close();
}

void Form_vvod::on_article_comboBox_currentIndexChanged(int index)
{
    ui->article_comboBox_num->setCurrentIndex(index);
    ui->number_comboBox->setCurrentIndex(index);
}

void Form_vvod::on_article_comboBox_num_currentIndexChanged(int index)
{
    ui->article_comboBox->setCurrentIndex(index);
    ui->number_comboBox->setCurrentIndex(index);
    ui->numberres_comboBox->setCurrentIndex(index);
}




void Form_vvod::on_number_comboBox_currentIndexChanged(int index)
{
  ui->article_comboBox->setCurrentIndex(index);
  ui->article_comboBox_num->setCurrentIndex(index);
  ui->numberres_comboBox->setCurrentIndex(index);

}

void Form_vvod::on_numberres_comboBox_currentIndexChanged(int index)
{
    ui->article_comboBox->setCurrentIndex(index);
    ui->article_comboBox_num->setCurrentIndex(index);
    ui->number_comboBox->setCurrentIndex(index);
}

void Form_vvod::on_dateEdit_v_userDateChanged(const QDate &date)
{
     data_t=date;
}
