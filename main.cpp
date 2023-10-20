#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>
#include <QSqlDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginDialog loginDialog;
    if (!LoginDialog().exec()) return 0;
    MainWindow w;
    w.show();
    return a.exec();
}
