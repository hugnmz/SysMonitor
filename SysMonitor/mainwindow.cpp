#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "systeminforworker.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    SystemInforWorker *worker = new SystemInforWorker();
    m_server = new SystemServer(this);

    connect(worker, &SystemInforWorker::dataUpdated, this, &MainWindow::updateInterface);
    connect(worker, &SystemInforWorker::publicIpReceive, [this](QString ip){
        ui->lblIPPublic->setText("IP Public: " + ip);
    });
    connect(worker, &SystemInforWorker::dataUpdated, m_server, &SystemServer::sendInfo);

    // kết nối signals

}


void MainWindow::updateInterface(double cpu, double ram, QString ip){
    ui->progressBarCPU->setValue(static_cast<int>(cpu));
        ui->progressBarRAM->setValue(static_cast<int>(ram));
        ui->labelIP->setText("IP Local: " + ip);
}

MainWindow::~MainWindow()
{
    delete ui;
}

