#include "articleform.h"
#include "ui_articleform.h"
#include "tableprinter.h"

#include <QPrinter>
#include <QPrintDialog>

class PrintBorder : public PagePrepare {
public:
    virtual void preparePage(QPainter *painter);
    static int pageNumber;
};

int PrintBorder::pageNumber = 0;

void PrintBorder::preparePage(QPainter *painter) {
    QRect rec = painter->viewport();
    painter->setPen(QPen(QColor(0, 0, 0), 1));
    painter->drawRect(rec);
    painter->translate(10, painter->viewport().height() - 10);
    painter->drawText(0, 0, QString("Page %1").arg(pageNumber));
    pageNumber += 1;
}

ArticleForm::ArticleForm(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArticleForm)
{
    ui->setupUi(this);

    ui->lineEdit_fed->setValidator(new QIntValidator(0, 999999999, this));



    modelarticle = new QSqlTableModel(this);
    modelarticle->setTable("article");
    modelarticle->setHeaderData(1, Qt::Horizontal,
                                        tr(" НОМЕР  "));
    modelarticle->setHeaderData(2, Qt::Horizontal,
                                   tr("СОДЕРЖАНИЕ СТАТЬИ"));
    modelarticle->setHeaderData(3, Qt::Horizontal,
                                   tr("СРОК НАКАЗАНИЯ"));
    modelarticle->setHeaderData(4, Qt::Horizontal,
                                   tr("СРОК НАКАЗАНИЯ РЕЦЕДИВ"));

    modelarticle->select();

    ui->tableView->setModel(modelarticle);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);

    modelarticle->select();

    modelfed = new  QSqlRelationalTableModel(this);
    modelfed->setTable("fed_search");

    articleInd = modelfed->fieldIndex("article");
    modelfed->setRelation(articleInd, QSqlRelation("article", "id", "text"));

    modelfed->setHeaderData(1, Qt::Horizontal,
                                        tr(" ФАМИЛИЯ ИМЯ ОТЧЕСТВО"));
    modelfed->setHeaderData(2, Qt::Horizontal,
                                  tr("ОТПЕЧАТОК"));
    modelfed->setHeaderData(3, Qt::Horizontal,
                                  tr("СТАТЬЯ"));

    ui->tableViewfed->setModel(modelfed);
    ui->tableViewfed->setColumnHidden(0,true);
    ui->tableViewfed->setSelectionBehavior(QAbstractItemView::SelectRows);

    ui->tableViewfed->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableViewfed->resizeColumnsToContents();
    ui->tableViewfed->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableViewfed->horizontalHeader()->setStretchLastSection(true);

     modelfed->select();



      QSqlQueryModel * model_art = new QSqlQueryModel();
      QSqlQuery * query_article = new QSqlQuery("Select text from article");
      query_article->exec();
      model_art->setQuery(*query_article);
      ui->art_comboBox->setModel(model_art);

      QSqlQueryModel * model_artnum = new QSqlQueryModel();
      QSqlQuery * query_article1= new QSqlQuery("Select nomer from article");
      query_article1->exec();
      model_artnum->setQuery(*query_article1);
      ui->artnum_comboBox->setModel(model_artnum);

      QSqlQueryModel *model_srok = new QSqlQueryModel();
      QSqlQuery * query_artsrok= new QSqlQuery("Select prison_term from article");
      query_artsrok->exec();
      model_srok->setQuery(*query_artsrok);
      ui->srok_comboBox->setModel(model_srok);

      QSqlQueryModel *model_res = new QSqlQueryModel();
      QSqlQuery * query_res= new QSqlQuery("Select prison_term_res from article");
      query_res->exec();
      model_res->setQuery(*query_res);
      ui->res_comboBox->setModel(model_res);

}

ArticleForm::~ArticleForm()
{
    delete ui;
}

void ArticleForm::on_pushButton_clicked()
{
QSqlQuery query;
query.prepare("INSERT INTO article (nomer, text,prison_term,prison_term_res) "
               "VALUES (:card_num, :card_text, :d_num, :d_num_srok)");
query.bindValue(":card_num",ui->N_lineEdit->text().toInt());
query.bindValue(":card_text",ui->A_textEdit->toPlainText());
query.bindValue(":d_num",ui->nak_spinBox->value());
query.bindValue(":d_num_srok",ui->res_spinBox->value());
query.exec();
modelarticle->select();
}



void ArticleForm::on_pushButton_2_clicked()
{
 ArticleForm::accept();
}

void ArticleForm::on_pushButton_4_clicked()
{
     QString Nomer_id,Number_tmp,stamp_id;

    Nomer_id=ui->artnum_comboBox->currentText();
    QSqlQuery qry;

    if (qry.exec("SELECT id FROM article WHERE nomer=\'" + Nomer_id +"\'"))
    {
        if (qry.next()) {
            Nomer_id=qry.value(0).toString();

            QString msg = "article.id = " + qry.value(0).toString() + "\n";
            QMessageBox::warning(this, "Nomer_id was successful", msg);

        }
    }


    QSqlQuery query;
    query.prepare("INSERT INTO fed_search (fio, stamp, article) "
                   "VALUES (:art_txt, :art_num, :t_num)");
    query.bindValue(":art_txt",ui->N_lineEdit_fed->text());
    query.bindValue(":art_num",ui->lineEdit_fed->text().toInt());
    query.bindValue(":t_num",Nomer_id.toInt());
    query.exec();

    modelfed->select();

}

void ArticleForm::on_artnum_comboBox_currentIndexChanged(int index)
{
    ui->art_comboBox->setCurrentIndex(index);
    ui->srok_comboBox->setCurrentIndex(index);
    ui->res_comboBox->setCurrentIndex(index);
}

void ArticleForm::on_art_comboBox_currentIndexChanged(int index)
{
    ui->artnum_comboBox->setCurrentIndex(index);
    ui->srok_comboBox->setCurrentIndex(index);
    ui->res_comboBox->setCurrentIndex(index);
}

void ArticleForm::on_srok_comboBox_currentIndexChanged(int index)
{
    ui->artnum_comboBox->setCurrentIndex(index);
    ui->art_comboBox->setCurrentIndex(index);
    ui->res_comboBox->setCurrentIndex(index);
}

void ArticleForm::on_res_comboBox_currentIndexChanged(int index)
{
    ui->artnum_comboBox->setCurrentIndex(index);
    ui->art_comboBox->setCurrentIndex(index);
    ui->srok_comboBox->setCurrentIndex(index);
}

void ArticleForm::on_pushButton_5_clicked()
{
     print();
}

void ArticleForm::print() {
   QPrinter *printer = new QPrinter;
   printer->setPageOrientation(QPageLayout::Portrait);
   printer->setPageSize(QPageSize::A4);

  QPrintDialog *dlg = new QPrintDialog(printer, this);
  dlg->exec();

 QSqlQuery query;
 query.exec("SELECT fio AS 'Фамилия Имя отчество', stamp as 'Код отпечатка',nomer as 'Номер статьи', text as 'Содержание статьи' FROM fed_search JOIN article ON fed_search.article = article.id");
 PrintTable(printer, query);
}

void ArticleForm::PrintTable( QPrinter* printer, QSqlQuery&  Query ) {
  QString strStream;
  QTextStream out(&strStream);

  const int rowCount = Query.size();

  const int columnCount = Query.record().count();

  out << QString("<p style = 'Text-Align: Center'> <Span Style = 'Spant-Size: 20.0pt; Font-Family: Song Body'>%1 </ span> </ p> \n ")
         .arg("Федеральный розыск");
  out   << QString("<p style = 'Text-Align: Prange'> <Span Style = 'Spant-Size: 18.0pt; Font-Family: Song Body'> Время печати:%1 </ span> </ p> \n ")
             .arg("26.04.2023");


  out <<  "<html>\n"
      "<head>\n"
      "<meta Content=\"Text/html; charset=Windows-1251\">\n"
      <<  QString("<title>%1</title>\n").arg("TITLE OF TABLE")
      <<  "</head>\n"
      "<body bgcolor=#ffffff link=#5000A0>\n"
      "<table border=1 cellspacing=0 cellpadding=2>\n";


  out << "<thead><tr bgcolor=#f0f0f0>";
  for (int column = 0; column < columnCount; column++)
    out << QString("<th>%1</th>").arg(Query.record().fieldName(column));
  out << "</tr></thead>\n";

  while (Query.next()) {
    out << "<tr>";
    for (int column = 0; column < columnCount; column++) {
      QString data = Query.value(column).toString();
      out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
    }
    out << "</tr>\n";
  }

  out <<  "</table>\n"
      "</body>\n"
      "</html>\n";

  QTextDocument document;
  document.setHtml(strStream);
  document.print(printer);

}

