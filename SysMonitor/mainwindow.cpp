#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "systeminforworker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SystemInforWorker *worker = new SystemInforWorker();

    connect(worker, &SystemInforWorker::dataUpdated, this, &MainWindow::updateInterface);

    // kết nối signals

}


void MainWindow::updateInterface(double cpu, double ram){
    ui->progressBarCPU->setValue(static_cast<int>(cpu));
        ui->progressBarRAM->setValue(static_cast<int>(ram));
}

MainWindow::~MainWindow()
{
    delete ui;
}

