#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include  <QSqlRelationalTableModel>
#include  <QTableView>
#include <QString>
#include <QDataWidgetMapper>
#include <QMessageBox>
enum {
    NEW_LIST_Id = 0,
    NEW_LIST_FIO = 1,
    NEW_LIST_STAMP = 2,
    NEW_LIST_ARTICLE = 3,
    NEW_LIST_NUMBER=4,
    NEW_LIST_DATAIN=5,
    NEW_LIST_DATAOUT=6
};


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QSqlDatabase db;

private slots:
    void on_pushBVvod_clicked();

    void on_Arcticle_pushButton_clicked();

    void on_listtableView_activated(const QModelIndex &index);

    void on_listtableView_clicked(const QModelIndex &index);

    void on_pushButton_3_clicked();

    void on_pushButton_2_clicked();

    void on_Arcticle_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;
   QDataWidgetMapper *mapper;

    QSqlRelationalTableModel *listmodel;
    QSqlTableModel *tabmodel,*numbermodel;
    QString date_str;
    int articleIndex, numberIndex;

};
#endif // MAINWINDOW_H
