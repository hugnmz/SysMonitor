#include "mainwindow.h"
#include "addstudent.h"
#include <QApplication>
#include <QtSql>
#include <QDebug>

void databaseInit(){
    QSqlQuery query;

    if(!query.exec("CREATE TABLE IF NOT EXISTS student("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                   "name TEXT)"))
    {
        qWarning() << "Create table error:" << query.lastError().text();
    }
}



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("st.db");
    if(!db.open()){
        qDebug() << "Not connect db";
        return -1;
    }

    qDebug() << "connect successfully";
    databaseInit();
    MainWindow w;
    w.show();
    return a.exec();
}
