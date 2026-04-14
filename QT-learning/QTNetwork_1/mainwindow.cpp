#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QNetworkAccessManager>
#include <QUrl>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QJsonObject> // tương đương với các cặp key : value
#include <QJsonDocument> // giúp chuyển đổi data thô QByteArray về cấu truc Json
#include <QDebug>
#include <QUrlQuery>
#include <QJsonArray>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // khời tạo qnetworkaccessmanager dùng để quản lí mạng và kết nối
    manager = new QNetworkAccessManager(this);

    getDataWeather();
}


void MainWindow::fetchData(){

    QUrl url("https://jsonplaceholder.typicode.com/todos/1");
    QNetworkRequest request(url);

    // thực hiện gửi request
    QNetworkReply *reply = manager->get(request);

    // kết nối tín hiệu khi hoàn thành
    connect(reply, &QNetworkReply::finished, [reply](){

        // neu ko co loi
        if(reply->error() == QNetworkReply::NoError){

            // doc du lieu tra ve
            QByteArray resData = reply->readAll();

            // phan tic Jon
            QJsonDocument jsonDoc = QJsonDocument::fromJson(resData);
            QJsonObject jsonObj = jsonDoc.object();

            qDebug() << "Title:" << jsonObj["title"].toString();
        }else {
            qDebug() << "Lỗi mạng:" << reply->errorString();
        }

        // giai phong bo nho cua reply
        reply->deleteLater();
    });
}


void MainWindow::getGithubInfo(){

    QUrl url("http://jsonplaceholder.typicode.com/todos/1");
    QNetworkRequest request(url);

    // lấy data trả veer
    QNetworkReply *reply = manager->get(request);

    // kết nối tín hiệu khi hoàn thành
    connect(reply, &QNetworkReply::finished, [reply](){
       if(reply->error() == QNetworkReply::NoError){

           QByteArray resData =reply->readAll();

           QJsonDocument jsonDoc = QJsonDocument::fromJson(resData);
           QJsonObject jsonObj = jsonDoc.object();

           QString name = jsonObj["title"].toString();

           qDebug() << name;

       }else {
           qDebug() << "Lỗi mạng:" << reply->errorString();
       }

       reply->deleteLater();

    });

}


void MainWindow::getDataWeather(){
    QString apiKety = "03e1b9e3bb45bcd5771d76b14b141d82";
    QString city = "Hanoi";

    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;
    query.addQueryItem("q", city);
    query.addQueryItem("appid", apiKety);
    query.addQueryItem("units", "metric");
    url.setQuery(query);


    QNetworkRequest request(url);
    QNetworkReply *reply = manager->get(request);

    connect(reply, &QNetworkReply::finished, [reply](){
       if(reply->error() == QNetworkReply::NoError){

           // lay data
           QByteArray responseData = reply->readAll();

           QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
           QJsonObject jsonObj = jsonDoc.object();

           QString cityName = jsonObj["name"].toString();

           // lấy thông tin lồng nhau
           QJsonObject mainObj = jsonObj["main"].toObject();
           double temp = mainObj["temp"].toDouble();
           int humidity = mainObj["humidity"].toInt();

           //lấy thông tin trong mảng
            QJsonArray weatherArray = jsonObj["weather"].toArray();
            QJsonObject firstWeatherObj = weatherArray.at(0).toObject();
            QString description = firstWeatherObj["description"].toString();

            // In kết quả
                        qDebug() << "--- THỜI TIẾT" << cityName << "---";
                        qDebug() << "Nhiệt độ:" << temp << "°C";
                        qDebug() << "Độ ẩm:" << humidity << "%";
                        qDebug() << "Mô tả:" << description;
       } else {
           qDebug() << "Lỗi API:" << reply->errorString();
       }
       reply->deleteLater();
    });
}
MainWindow::~MainWindow()
{
    delete ui;
}

