#include "systeminforworker.h"
#include <windows.h>

SystemInforWorker::SystemInforWorker(QObject *parent) :QObject(parent){
    m_timer = new QTimer(this);

    // 1s update 1 lần
    connect(m_timer, &QTimer::timeout, this, &SystemInforWorker::fetchStats);
    m_timer->start(1000);
}

void SystemInforWorker::fetchStats(){
    double cpu = getCpuUsage();
    double ram = getRamUsage();

    emit dataUpdated(cpu, ram); // phát ra tín hiệu chứa dữ liệu
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
