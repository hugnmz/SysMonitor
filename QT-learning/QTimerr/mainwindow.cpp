#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTimer>

QTimer *timer;
int cnt = 10;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer();
    timer->setInterval(1000);
    connect(timer, SIGNAL(timer_timeout()), this, SLOT(timer_timeout()));
    timer->start();
}

void MainWindow::timer_timeout(){
    ui->lblNumber->setText(QString::number(--cnt));

    if(cnt == 0) this->close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

