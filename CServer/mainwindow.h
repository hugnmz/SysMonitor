#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void newMessage(QString);

private slots:
    void newConnection();
    void appendToSocketList(QTcpSocket*);
    void discardSocket();
    void readSocket();
    void displayMessage(const QString& str);
    void displayError(QAbstractSocket::SocketError socketError);
    void sendMessage(QTcpSocket*);
    void sendAttachment(QTcpSocket*, QString filePath);

    void on_pushButton_sendMessage_clicked();
    void on_pushButton_sendAttachment_clicked();

    void refreshComboBox();


private:
    QTcpServer *server;
    QSet<QTcpSocket*> set;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
