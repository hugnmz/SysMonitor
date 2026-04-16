#ifndef RSSLISTING_H
#define RSSLISTING_H

#include <QWidget>
#include <QString>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QLineEdit>
#include <QTreeWidget>
#include <QPushButton>



QT_BEGIN_NAMESPACE
namespace Ui { class RSSListing; }
QT_END_NAMESPACE

class RSSListing : public QWidget
{
    Q_OBJECT

public:
    RSSListing(const QString &url = QString(), QWidget *parent = nullptr);
    ~RSSListing();
public slots:
    void  fetch();
    void finished(QNetworkReply *reply);
    void consumeData();
    void error(QNetworkReply::NetworkError);

private:
    void parseXml();
        void get(const QUrl &url);

        // Parser state:
        QXmlStreamReader xml;
        QString currentTag;
        QString linkString;
        QString titleString;

        // Network state:
        QNetworkAccessManager *manager;
        QNetworkReply *currentReply;

        // UI elements:
        QLineEdit *lineEdit; // cung cấp input của URL
        QTreeWidget *treeWidget; // hiển thị kết quả mỗi khi fetch
        QPushButton *fetchButton;
};
#endif // RSSLISTING_H
