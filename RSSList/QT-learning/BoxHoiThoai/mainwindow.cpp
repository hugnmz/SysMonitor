#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnInformation_clicked()
{
    QMessageBox::information(this, "info", "Chào các bạn");
}

void MainWindow::on_btnWarning_clicked()
{
    QMessageBox::information(this, "warning", "Đây là thoại cảnh báo");

}

void MainWindow::on_btnQuestion_clicked()
{
    if(QMessageBox::question(this, "question", "Bạn có ok ko", QMessageBox::Ok | QMessageBox::Cancel) == QMessageBox::Yes )
        this->setWindowTitle("Yes");
    else
        this->setWindowTitle("No");

}

void MainWindow::on_btnCritical_clicked()
{
    QMessageBox::information(this, "critical", "Quan Trọng");

}
