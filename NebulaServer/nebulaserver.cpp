#include "nebulaserver.h"
#include <QThread>
#include <SslWorker.h>


NebulaServer::NebulaServer()
{

}


void NebulaServer::incomingConnection(qintptr socketDescriptor){
    // tạo thread mới để cho socket Descriptor vào. phục vụ cho từng client.
    QThread* thread = new QThread;

    // tạo 1 socket với đã định danh đã được tạo sẵn bởi server(lúc này worker vẫn nằm ở luồng chính)
    SslWorker* worker = new SslWorker(socketDescriptor);

    // đưa worker vào thread vừa được tạo
    worker->moveToThread(thread);

    // khi luồng chạy ra lện cho worker làm viẹc
    connect(thread, &QThread::start, worker, &SslWorker::process);

    // khi dừng luồng sẽ phải đóng luồng lại
    connect(thread, &QThread::finished, thread, &QThread::quit);

    // sau khi dừng luồng sẽ thực hiện xóa khỏi bộ nhớ
    connect(worker, &SslWorker::finished, worker, &SslWorker::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);
}
