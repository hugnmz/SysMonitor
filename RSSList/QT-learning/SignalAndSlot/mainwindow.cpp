#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnSayHello, &QPushButton::clicked, this, &MainWindow::displayText); // displayText là hàm phải thuojc this
}


void MainWindow::displayText(){
    ui->lblHello->setText("Xin chao Hung");
}


MainWindow::~MainWindow()
{
    delete ui;
}



