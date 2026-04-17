#include "systemclient.h"
#include "ui_systemclient.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

systemclient::systemclient(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::systemclient)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
}

systemclient::~systemclient()
{
    delete ui;
}

void systemclient::on_btnConnect_clicked()
{
    QString strIp = ui->lineInput->text();
    socket->abort();
    socket->connectToHost(strIp, 8082);
}



