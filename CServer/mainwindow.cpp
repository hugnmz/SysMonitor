#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QMessageBox>
#include <QMetaType>
#include <QSet>
#include <QStandardPaths>
#include <QTcpServer>
#include <QTcpSocket>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    server = new QTcpServer(this);


    // lắng nghe port 8086
    if(server->listen(QHostAddress::Any, 8086)){

        connect(server, &QTcpServer::newConnection, this, &MainWindow::newConnection);

        // khi kết nối thành công sẽ phát ra signal newMessage
        connect(this, &MainWindow::newMessage, this, &MainWindow::displayMessage);

        ui->statusBar->showMessage("Connecting...");

    }else
    {
        QMessageBox::critical(this,"QTCPServer",QString("Unable to start the server: %1.").arg(server->errorString()));
        exit(EXIT_FAILURE);
    }

}

// thực hiện tạo connect mới
void MainWindow::newConnection(){

    // check xem có bao nhiêu người đang kết nếu
    while (server->hasPendingConnections()) {

        // chấp nhận kết nối và trả vê 1 object QTcpSocket thêm vào set để quản lí
        appendToSocketList(server->nextPendingConnection());
    }
}

void MainWindow::appendToSocketList(QTcpSocket* socket){

    // thêm 1 socket vào set
    set.insert(socket);
    connect(socket, &QTcpSocket::readyRead, this, &MainWindow::readSocket);
    connect(socket, &QTcpSocket::disconnected, this, &MainWindow::discardSocket);
    ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
    displayMessage(QString("INFO :: Client with sockd:%1 has just entered the room").arg(socket->socketDescriptor()));
}

// bóc tách và xử lí dũ liệu nhận về
void MainWindow::readSocket(){

    // xác nhận socket nào gửi
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());

    // tạo 1 byte array để hứng data
    QByteArray buffer;

    QDataStream socketStream(socket);
    socketStream.setVersion(QDataStream::Qt_5_12);

    socketStream.startTransaction();

    // đọc toàn bộ gói tin được gửi
    socketStream >> buffer;

    // kiểm tra xem số byte được nhận đã đủ chưa
    if(!socketStream.commitTransaction())
    {
        QString message = QString("%1 :: Waiting for more data to come..").arg(socket->socketDescriptor());
        emit newMessage(message);
        return;
    }

    // cắt ra đúng 128 byte đầu
    QString header = buffer.mid(0, 128);
    QString fileType = header.split(",")[0].split(":")[1];

    buffer = buffer.mid(128); // cắt xong thì bỏ 128 byte đầu đi

    if(fileType == "attachment"){

        QString fileName = header.split(",")[1].split(":")[1];
        QString ext = fileName.split(".")[1];
        QString size = header.split(",")[2].split(":")[1].split(";")[0];

        if (QMessageBox::Yes == QMessageBox::question(this, "CServer", QString("You are receiving an attachment from sd:%1 of size: %2 bytes, called %3. Do you want to accept it?").arg(socket->socketDescriptor()).arg(size).arg(fileName))){
            QString filePath = QFileDialog::getSaveFileName(this, tr("Save File"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)+"/"+fileName, QString("File (*.%1)").arg(ext));

                        QFile file(filePath);
                        if(file.open(QIODevice::WriteOnly)){
                            file.write(buffer);
                            QString message = QString("INFO :: Attachment from sd:%1 successfully stored on disk under the path %2").arg(socket->socketDescriptor()).arg(QString(filePath));
                            emit newMessage(message);
                        }else
                            QMessageBox::critical(this,"CServer", "An error occurred while trying to write the attachment.");
                    }else{
                        QString message = QString("INFO :: Attachment from sd:%1 discarded").arg(socket->socketDescriptor());
                        emit newMessage(message);
                    }
                }else if(fileType=="message"){
                    QString message = QString("%1 :: %2").arg(socket->socketDescriptor()).arg(QString::fromStdString(buffer.toStdString()));
                    emit newMessage(message);
                }
    }



void MainWindow::discardSocket(){

    // lấy ra socket vừa thoát
    QTcpSocket* socket = reinterpret_cast<QTcpSocket*>(sender());

    // tìm nó có trong danh sách ko
    QSet<QTcpSocket*>::iterator it = set.find(socket);

    if(it != set.end()){
       set.remove(*it);
    }

    refreshComboBox();
    socket->deleteLater();

}

void MainWindow::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
        case QAbstractSocket::RemoteHostClosedError:
        break;
        case QAbstractSocket::HostNotFoundError:
            QMessageBox::information(this, "QTCPServer", "The host was not found. Please check the host name and port settings.");
        break;
        case QAbstractSocket::ConnectionRefusedError:
            QMessageBox::information(this, "QTCPServer", "The connection was refused by the peer. Make sure QTCPServer is running, and check that the host name and port settings are correct.");
        break;
        default:
            QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
            QMessageBox::information(this, "QTCPServer", QString("The following error occurred: %1.").arg(socket->errorString()));
        break;
    }
}

void MainWindow::on_pushButton_sendMessage_clicked(){
    QString receiver = ui->comboBox_receiver->currentText();

    if(receiver == "Broadcast"){
        foreach(QTcpSocket* socket, set){
            sendMessage(socket);
        }
    }else{
        foreach(QTcpSocket* socket, set){
            if(socket->socketDescriptor() == receiver.toLongLong()){
                sendMessage(socket);
                break;
            }
        }
    }

}


void MainWindow::on_pushButton_sendAttachment_clicked(){

    // lấy ra chữ hiển thị trên thanh comboBox_receiver
    QString receiver = ui->comboBox_receiver->currentText();

    QString filePath = QFileDialog::getOpenFileName(this, ("Select an attachment"), QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation), ("File (*.json *.txt *.png *.jpg *.jpeg)"));

    if(filePath.isEmpty()){
        QMessageBox::critical(this, "CServer", "file empty");
        return;
    }

    if(receiver=="Broadcast"){

        // gửi hết cho từng người
        foreach(QTcpSocket* socket, set){
            sendAttachment(socket, filePath);
        }
    }
    // gửi cho người được hconj cụ thể
    else{

        foreach(QTcpSocket* socket, set){
            if(socket->socketDescriptor() == receiver.toLongLong()){
                sendAttachment(socket, filePath);
                break;
            }
        }

    }
}

void MainWindow::sendMessage(QTcpSocket* socket){
    if(socket){
        if(socket->isOpen()){
            QString mess = ui->lineEdit_message->text();

            // tạo ra công cụ đóng gói tự động và gắn vào socket
            QDataStream socketStream(socket);

            socketStream.setVersion(QDataStream::Qt_5_12);
            QByteArray header;
            header.prepend(QString("fileType:message,fileName:null,fileSize:%1;").arg(mess.size()).toUtf8());
            header.resize(128);

            QByteArray byteArray = mess.toUtf8();
            byteArray.prepend(header);

            socketStream.setVersion(QDataStream::Qt_5_12);
            socketStream << byteArray;
        }else
            QMessageBox::critical(this,"QTCPServer","Socket doesn't seem to be opened");
    }
    else
        QMessageBox::critical(this,"QTCPServer","Not connected");
}


// xử lí việc gửi tệp tin qua mạng
void MainWindow::sendAttachment(QTcpSocket* socket, QString filePath){
    if(socket){
        if(socket->isOpen()){

            //khởi tạo đối tượng QFile để làm việc với file từ đường dẫn
            QFile file(filePath);

            // mở file ở chế độ chỉ đọc
            if(file.open(QIODevice::ReadOnly)){

                // lấy thông tin metadata của file
                QFileInfo fileInfo(file.fileName());

                // tách tên file ra khỏi đường dẫn
                QString fileName(fileInfo.fileName());

                // đóng goi dữ liệu. chuyển đổi sang dạng byte array để truyền qua mạng
                QDataStream socketStream(socket);

                socketStream.setVersion(QDataStream::Qt_5_12);

                // set header
                QByteArray header;
                header.prepend(QString("fileType:attachment,fileName:%1,fileSize:%2;").arg(fileName).arg(file.size()).toUtf8());

                // resize: tạo ra 1 khung chứa cố định thông tin mô tả file
                header.resize(128);

                QByteArray byteArray = file.readAll();
                byteArray.prepend(header);

                socketStream.setVersion(QDataStream::Qt_5_12);
                socketStream << byteArray;
            }else {
                // Thông báo lỗi nếu file bị khóa hoặc không có quyền đọc
                QMessageBox::critical(this,"CServer","Couldn't open the attachment!");
            }

        }else{
            QMessageBox::critical(this, "CServer", "Socket isn't connected");
        }
    }else{
        QMessageBox::critical(this, "CServer", "Not connect");
    }
}

// hiển thị message
void MainWindow::displayMessage(const QString& message){
    ui->textBrowser_receivedMessages->append(message);
}

// refresh khi append hoặc delete 1 socket
void MainWindow::refreshComboBox(){

    // xoa het nhung ng co trong combobox
    ui->comboBox_receiver->clear();
    ui->comboBox_receiver->addItem("Broadcast");

    foreach(QTcpSocket* socket, set){
        ui->comboBox_receiver->addItem(QString::number(socket->socketDescriptor()));
    }


    // socketDescriptor: số nguyên định danh duy nhất mà OS cấp cho mỗi kết nối
}

MainWindow::~MainWindow()
{

    foreach(QTcpSocket* socket, set){
        socket->close();
        socket->deleteLater();
    }


    server->close();
    server->deleteLater();
    delete ui;
}

