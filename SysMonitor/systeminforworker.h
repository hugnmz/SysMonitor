#ifndef SYSTEMINFORWORKER_H
#define SYSTEMINFORWORKER_H
/*
    -Class này sẽ lấy thông số lên
*/

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkAccessManager>

class SystemInforWorker : public QObject{
    Q_OBJECT

public:
    explicit SystemInforWorker(QObject *parent = nullptr);

signals:
    // signal gửi data ra ngoài
    void dataUpdated(double cpu, double ram, QString ip);


signals:
    void publicIpReceive(const QString &ip);
// hàm lấy data
private slots:
    void fetchStats();

QString getLocalIp();
void getPublicIp();


private:
    QTimer *m_timer;
    QNetworkAccessManager *manager;
    double getCpuUsage();
    double getRamUsage();
};
#endif // SYSTEMINFORWORKER_H
