#include<SystemServer.h>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <systeminforworker.h>


SystemServer::SystemServer(QObject *parent): QTcpServer(parent){

    if(this->listen(QHostAddress::Any, 8090)){

        connect(this, &QTcpServer::newConnection, this, &SystemServer::newConnection);
    }else
    {
        qDebug() << "SERVER ERROR:" << this->errorString();
        exit(EXIT_FAILURE);
    }
}

void SystemServer::newConnection(){
    while(this->hasPendingConnections()){
        appendToSocketList(this->nextPendingConnection());
    }
}

void SystemServer::appendToSocketList(QTcpSocket* socket){

    set.insert(socket);
}

void SystemServer::sendInfo(double cpu, double ram, QString localIp){
    QString mess = QString("CPU: %1% RAM: %2% IP: %3").arg(cpu).arg(ram).arg(localIp);
    QByteArray header;
    header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(mess.size()).toUtf8());
    header.resize(128);

    QByteArray byteArray = mess.toUtf8();
    byteArray.prepend(header);
    for(QTcpSocket* s : set){
        if(s->state() == QTcpSocket::ConnectedState){
            QDataStream socketStream(s);

            socketStream.setVersion(QDataStream::Qt_5_12);

            socketStream << byteArray;
            s->flush();

        }
    }
}

