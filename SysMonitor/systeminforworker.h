#ifndef SYSTEMINFORWORKER_H
#define SYSTEMINFORWORKER_H
/*
    -Class này sẽ lấy thông số lên
*/

#include <QObject>
#include <QTimer>

class SystemInforWorker : public QObject{
    Q_OBJECT

public:
    explicit SystemInforWorker(QObject *parent = nullptr);

signals:
    // signal gửi data ra ngoài
    void dataUpdated(double cpu, double ram);

// hàm lấy data
private slots:
    void fetchStats();


private:
    QTimer *m_timer;
    double getCpuUsage();
    double getRamUsage();
};
#endif // SYSTEMINFORWORKER_H
