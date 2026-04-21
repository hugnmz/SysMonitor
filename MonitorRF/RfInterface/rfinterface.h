#ifndef RFINTERFACE_H
#define RFINTERFACE_H

#include "RfInterface_global.h"
#include <QObject>
#include <QObject>
#include <QVector>
#include <QtPlugin>

// định nghĩa các gói tin dữ liệu
struct RfDataPacket{
    double centerFrequency; // đo lại tần số trung tâm tại thời điểm đo
    double bandwidth; // băng thông của đài quét
    qint64 time; // thời gian chính xác lúc thu mẫu (mili)
    QVector<double> magnitude; // mảng chứa cường độ tín hiệu (dBm) sau khi xử lí FFT
};

class RFINTERFACE_EXPORT RfInterface : public QObject
{
    Q_OBJECT
public:
    explicit RfInterface(QObject *parent = nullptr);

    // destructor
    virtual ~RfInterface(){}

    virtual bool setupDevice(QString params) = 0; // khởi tạo phần cứng

    virtual bool setTunedFrequency(double mhz) = 0; // ép máy đo nhảy sang tần số chỉ định

    virtual void startStream() = 0; // bắt đâuù lấy data về

    virtual void endStream() = 0; // dừng lấy data


signals:
    void dataReady(const RfDataPacket &data); // phát ra tín hiệu về cho Host
};

// 3. Khai báo định danh Interface cho Qt
#define RfInterface_IID "com.monitorrf.RfInterface"
Q_DECLARE_INTERFACE(RfInterface, RfInterface_IID)

#endif // RFINTERFACE_H
