#include "SslWorker.h"
#include <QDataStream>
#include "protocol.h"
#include "appconfig.h"
#include "nebulacommon.h"
#include "QJsonObject"
#include "QJsonDocument"

SslWorker::SslWorker(qintptr socketDescriptor){
    m_descriptor = socketDescriptor;
    m_expectedSize = 16;
}

void SslWorker::process(){

    // tạo mới 1 socket cho client này
    m_socket = new QSslSocket(this);

    // set socketDescriptor cho client nayf
    if(m_socket->setSocketDescriptor(m_descriptor)){
        // Cấu hình chứng chỉ
        m_socket->setLocalCertificate("server.crt");
        m_socket->setPrivateKey("server.key");
        m_socket->setProtocol(QSsl::TlsV1_2OrLater);

        // signal đọc data gửi đến
        connect(m_socket, &QSslSocket::readyRead, this, &SslWorker::onReadyRead);

        // bắt đầu bắt tay Ssl
        m_socket->startServerEncryption();
    }
}

void SslWorker::onReadyRead(){

    // lấy toàn bộ data từ socket vòa buffer đã tạo
    buffer.append(m_socket->readAll());

    // vòng lặp để xử lí cho đến khi ko còn dữ liệu trong buffer
    while(true){

        //đọc header
        if(m_state == ReadingHeader){

            // nếu chưa đủ 16 byte cố định header sẽ dừng
            if(static_cast<quint64>(buffer.size()) < m_expectedSize){
                return;
            }

            // nếu đã gom đủ thì sẽ phân tích header
            // giải mã header
            QDataStream ds(buffer.left(16));
            quint32 magic; quint16 ver, type; quint64 size;
            ds >> magic >> ver>> type>> size; // lấy dữ liệu theo đúng thứ tư 16 byte;

            // check có đúng định dạng ko
            if(magic != 0x4E424C41){
                m_socket->disconnectFromHost(); // ngắt kết nối ngay lập tức
                return;
            }

            // ghi nhớ thông tin header để chuẩn bị đọc phần payload;
            m_currentPacketType = type;
            m_state = ReadingPayload;
            buffer.remove(0, 16); // xóa phần header đã đọc
            m_expectedSize = size; // cập nhật lại size để biết còn bao nhieu byte phải đọc
        }

        // check nếu payload
        if(m_state == ReadingPayload){
            if(static_cast<quint64>(buffer.size()) < m_expectedSize){
                return;
            }

            // giải mã payload
            QByteArray payload = buffer.left(m_expectedSize);

            // gọi làm xử lí logic
            processPacket(m_currentPacketType,payload);

            buffer.remove(0, m_expectedSize); //xóa phần thân đã ử lí xong
            m_state = ReadingHeader; // quay lại trạng thái chờ của header
            m_expectedSize = 16; // đặt lại mục tiêu chờ của header;

            if(buffer.isEmpty()) break;
        }
    }
}

void SslWorker::processPacket(int type ,const QByteArray &payload){

    // ép kiểu type về enum PacketType
    Nebula::PacketType packetType = static_cast<Nebula::PacketType>(type);
    switch (type) {

        // xác thực authen
        case Nebula::Auth_Response:
        handleAuthentication(payload);
        break;


        // giám sát hệ thống
    case Nebula::Get_Sys_Stats:
        break;
        // --- NHÓM 3: TRUYỀN FILE (FILE TRANSFER) ---
                case Nebula::File_Header:
                    break;

                case Nebula::File_Chunk:
                    handleFileChunk(payload);
                    break;

                default:
                    qWarning() << "Unknown Packet Type:" << type;
                    break;
    }

}


// kiểm tra bảo mật dữ liệu truyền về từ client
void SslWorker::handleAuthentication(const QByteArray &data){

    // CLient gửi password xác thực
    QString receiveHash = QString::fromUtf8(data);
    QString expectedHash = AppConfig::instance().getPwdHash();

    if(expectedHash != receiveHash){
        qWarning() << "Auth failed! Disconnecting...";
    m_socket->write(wrapPacket(Nebula::Auth_Failed, "Wrong Password"));
    m_socket->disconnectFromHost();

    }else{
        m_isAuthen = true;
        qDebug() << "Client authenticated!";
        m_socket->write(wrapPacket(Nebula::Auth_Success, "Success"));
    }
}

void SslWorker::handleSystemStatusRequest(){
    if(!m_isAuthen) return;

    QJsonObject status;
        status["cpu"] = 15; // Sau này dùng class SysInfo để lấy số thực
        status["ram"] = 45;
        status["uptime"] = "12:30:05";

        // Chuyển JSON sang mảng Byte để gửi qua Network
        QJsonDocument doc(status);
        m_socket->write(wrapPacket(Nebula::Sys_Stats_Reply, doc.toJson()));

}

// xử lí việc tải file
void SslWorker::handleFileChunk(const QByteArray &data){
    if(!m_isAuthen) return;

    m_targetFile->write(data);
    m_targetFile->flush();
    emit processUpdated(m_targetFile->size());

    return;
}

void SslWorker::handleFileHeader(const QByteArray &data){

    // chuyeenr dataa thanfh QJsonDocument
    QJsonDocument doc = QJsonDocument::fromJson(data);


    // lấy ra filename và file size

    if(!doc.isNull()){

        // chuyeenr sang json object
        QJsonObject json = doc.object();
    }
    // dọn dẹp


    // tạo file mới và mở luồng ghi

    // thông báo trạng thái
}

