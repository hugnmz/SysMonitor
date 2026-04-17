#include "systeminforworker.h"
#include <windows.h>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QUrl>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

SystemInforWorker::SystemInforWorker(QObject *parent) :QObject(parent){
    m_timer = new QTimer(this);
    manager =  new QNetworkAccessManager(this);
    // 1s update 1 lần
    connect(m_timer, &QTimer::timeout, this, &SystemInforWorker::fetchStats);
    m_timer->start(1000);
}

void SystemInforWorker::fetchStats(){
    double cpu = getCpuUsage();
    double ram = getRamUsage();
    QString ip = getLocalIp();
    getPublicIp();
    emit dataUpdated(cpu, ram, ip); // phát ra tín hiệu chứa dữ liệu
}


double SystemInforWorker::getRamUsage() {
    MEMORYSTATUSEX memInfo;
    memInfo.dwLength = sizeof(MEMORYSTATUSEX);
    GlobalMemoryStatusEx(&memInfo);
    return (double)memInfo.dwMemoryLoad;
}

// lay thong tin ve cpu
double SystemInforWorker::getCpuUsage(){


    static ULONGLONG lastIdleTime = 0, lastKernelTime =0, lastUserTime = 0;
    FILETIME idleTime, kernelTime, userTime; // filetime đếm 100ns mỗi lần

    if(!GetSystemTimes(&idleTime, &kernelTime, &userTime)) return 0;

    // chuyển dạng FILETIME sang ULONGLONG
    auto ft2ull = [](const FILETIME& ft){
        ULARGE_INTEGER uli;
        uli.LowPart = ft.dwLowDateTime;
        uli.HighPart = ft.dwHighDateTime;
        ULONGLONG result = uli.QuadPart;

        return result;
    };

    ULONGLONG nowIdle = ft2ull(idleTime);
    ULONGLONG nowKernel = ft2ull(kernelTime);
    ULONGLONG nowUser = ft2ull(userTime);

    // tính độ chênh lệch giữa 2 thời điểm
    ULONGLONG diffIdle = nowIdle - lastIdleTime;
    ULONGLONG diffKernel = nowKernel - lastKernelTime;
    ULONGLONG diffUser = nowUser - lastUserTime;
    ULONGLONG diffTotal = diffKernel + diffUser;

        // Lưu lại giá trị cho lần gọi sau
        lastIdleTime = nowIdle;
        lastKernelTime = nowKernel;
        lastUserTime = nowUser;

        if (diffTotal == 0) return 0;

        // return ve % CPU dang hd
        return (double)(diffTotal - diffIdle) * 100/diffTotal;
}

QString SystemInforWorker::getLocalIp(){
    const QHostAddress &local = QHostAddress(QHostAddress::LocalHost);


    for(const QHostAddress &address : QNetworkInterface::allAddresses()){
        if(address != local && address.protocol() == QAbstractSocket::IPv4Protocol) return address.toString();
    }

    return local.toString();
}

void SystemInforWorker::getPublicIp(){



    QUrl url("http://api.ipify.org");
    QNetworkRequest request(url);

    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished,[this, reply](){
       if(reply->error() == QNetworkReply::NoError){
           QByteArray responseData = reply->readAll();

           QString rs = QString::fromUtf8(responseData);
           emit publicIpReceive(rs);
       }

       reply->deleteLater();
    });
}
