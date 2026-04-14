#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QDebug>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QString str1 = "Hello world";
    // this->setWindowTitle(str1);

    qDebug()<< str1;

    QString str2 = QString(3, 'X');
    qDebug() << str2;

    qDebug() << str2.length();
    str1.chop(2); // xóa đi n kí từ từ cuối chuỗi

    qDebug()<< str1;

   str1.truncate(2); // bỏ bớt kí tự ở chuỗi tính từ vị trí n
   qDebug()<< str1;

    // đổi từ số sang chuỗi
   int i = 10;
   QString str = QString::number(i);
}


MainWindow::~MainWindow()
{
    delete ui;
}

