#ifndef NEBULASERVER_H
#define NEBULASERVER_H
#include <QTcpServer>

class NebulaServer : public QTcpServer
{
    Q_OBJECT
public:
    NebulaServer();

public:
    void incomingConnection(qintptr socketDescriptor) override;
};



#endif // NEBULASERVER_H
