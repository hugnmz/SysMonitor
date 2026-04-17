#ifndef SSLWORKER_H
#define SSLWORKER_H

#include <QObject>
#include <QtNetwork/QSslError>
#include <QtNetwork/QSslSocket>
#include <QFile>


// class sẽ tồn tại trong 1 class riêng và sẽ quản lí 1 client
class SslWorker : public QObject{

    Q_OBJECT
public:
    SslWorker(qintptr socketDescriptor);

    enum ReadingState{
         ReadingHeader, // đợi đủ 16 byte header
         ReadingPayload // đã có header đang đợi payload
    };

signals:
    void finished();
    void processUpdated(int size);
public slots:
    void process(); // hàm khởi chạy trong thread;
    void onReadyRead();
//    void onSslError(const QList<QSslError> &errors);
    void processPacket(int type ,const QByteArray &payload);
    void handleAuthentication(const QByteArray &data);
    void handleSystemStatusRequest();
    void handleFileChunk(const QByteArray &data);
    void handleFileHeader(const QByteArray &data);


private:
    int m_currentPacketType;
    ReadingState m_state;
    QByteArray buffer; // dùng để hứng data
    quint64 m_expectedSize; // con số mục tiêu cần đạt  được để xử lí tiếp
    qintptr m_descriptor;
    QSslSocket *m_socket;
    bool m_isAuthen = false;
    QFile *m_targetFile = nullptr;

};

#endif // SSLWORKER_H
