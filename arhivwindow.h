#ifndef ARHIVWINDOW_H
#define ARHIVWINDOW_H
#include <QDialog>
#include <QString>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlTableModel>
#include <QSqlQuery>

namespace Ui {
class arhivWindow;
}

class arhivWindow : public  QDialog
{
    Q_OBJECT

public:
    explicit arhivWindow(QWidget *parent = nullptr);
    ~arhivWindow();

private:
    Ui::arhivWindow *ui;
    QSqlQueryModel *model_arh;
    QSqlTableModel *modelarh;
};

#endif // ARHIVWINDOW_H
