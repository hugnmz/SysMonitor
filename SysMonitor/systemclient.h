#ifndef SYSTEMCLIENT_H
#define SYSTEMCLIENT_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>

namespace Ui {
class systemclient;
}

class systemclient : public QWidget
{
    Q_OBJECT

public:
    explicit systemclient(QWidget *parent = nullptr);
    ~systemclient();

private slots:
    void on_btnConnect_clicked();

private:
    Ui::systemclient *ui;
    QTcpSocket *socket;
};

#endif // SYSTEMCLIENT_H
