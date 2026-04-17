#ifndef NEBULACOMMON_H
#define NEBULACOMMON_H

#include <QtGlobal>
#include <QByteArray>
#include <QDataStream>

// đóng gói data thô thành gói tin để gửi. đúng theo tiêu chuẩn yêu cầu
static QByteArray wrapPacket(quint16 type, const QByteArray &data) {

    QByteArray packet;

    // sử dụng QDataStream đẻe ghi từng byte vào QDataArray
    QDataStream out(&packet, QIODevice::WriteOnly);

    // thiết lập thứ tự byte đồng bộ giữa các Os
    out.setByteOrder(QDataStream::BigEndian);

    // thực hienj ghi header
    // 1. Ghi Magic Number (4 bytes): Để nhận diện đây là gói tin của hệ thống Nebula
        // 0x4E424C41 tương ứng với chuỗi ký tự "NBLA" trong bảng mã ASCII
        out << (quint32)0x4E424C41;

        // 2. Ghi Version (2 bytes): Phiên bản giao thức, hiện tại là 0x0001
        out << (quint16)0x0001;

        // 3. Ghi Type (2 bytes): Loại gói tin mà bạn truyền vào tham số
        out << (quint16)type;

        // 4. Ghi Size (8 bytes): Độ dài của phần dữ liệu thực tế (Payload)
        // Phía nhận sẽ đọc số này để biết cần phải đợi thêm bao nhiêu byte nữa
        out << (quint64)data.size();

       //thực hiện ghi payload
       packet.append(data);

       return packet;
}

class NebulaCommon
{
public:
    NebulaCommon();
};

#endif // NEBULACOMMON_H
