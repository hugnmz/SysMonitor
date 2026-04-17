#include "nebulaserver.h"
#include <QThread>

NebulaServer::NebulaServer()
{

}


void NebulaServer::incomingConnection(qintptr socketDescriptor){
    // tạo thread mới để cho socket Descriptor vào
    QThread* thread = new QThread;
}
