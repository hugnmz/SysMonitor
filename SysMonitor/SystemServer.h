#ifndef SYSTEMSERVER_H
#define SYSTEMSERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>


class SystemServer : public QTcpServer{
    Q_OBJECT

public:
    explicit SystemServer(QObject *parent = nullptr);


signals:
    void clientConnected();

public slots:
    void newConnection();
    void appendToSocketList(QTcpSocket*);
    void sendInfo(double cpu, double ram, QString localIp);

private:
    QSet<QTcpSocket*> set;
    QTcpSocket *socket;
};

#endif // SYSTEMSERVER_H
