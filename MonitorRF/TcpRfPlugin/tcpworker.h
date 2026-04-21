#ifndef TCPWORKER_H
#define TCPWORKER_H

/*
    đóng vai trò quản lí socket - xử l í bất đồng bộ và tính toán FFT
*/

#include <QObject>
#include <QTcpSocket>
#include "rfinterface.h"

class TcpWorker : public QObject{
    Q_OBJECT
    public:
};

#endif // TCPWORKER_H
