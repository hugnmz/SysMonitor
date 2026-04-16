#include "rsslisting.h"
#include "ui_rsslisting.h"
#include <QDesktopServices>
#include <QHBoxLayout>
#include <QVBoxLayout>

RSSListing::RSSListing(const QString &url,QWidget *parent)
    : QWidget(parent)
    , currentReply(0)
{

    // tải dữ liệu xong thì gọi hàm này
    connect(manager, &QNetworkAccessManager::finished, this, &RSSListing::finished);

    // tạo ô để người dùng nhập địa chỉ
    lineEdit = new QLineEdit(this);
    lineEdit->setText(url); // hiển thị đường dẫn mặc định lên ô nhập

    //ấn entern sẽ lấy data lên
    connect(lineEdit, &QLineEdit::returnPressed, this, &RSSListing::fetch);

    //khi click nút cũng sẽ fetch data
    fetchButton = new QPushButton(tr("Fetch"), this);
    connect(fetchButton, &QPushButton::clicked, this, &RSSListing::fetch);

    // tọa 1 bảng danh sách để hiện tiêu đề bài báo và link
    treeWidget = new QTreeWidget(this);
    treeWidget = new QTreeWidget(this);
        connect(treeWidget, &QTreeWidget::itemActivated,
                // Open the link in the browser:
                this, [](QTreeWidgetItem *item) { QDesktopServices::openUrl(QUrl(item->text(1))); });
        treeWidget->setHeaderLabels(QStringList { tr("Title"), tr("Link") });
        treeWidget->header();

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(lineEdit);
        hLayout->addWidget(fetchButton);

        QVBoxLayout *vLayout = new QVBoxLayout(this);
            vLayout->addLayout(hLayout);
            vLayout->addWidget(treeWidget);

            setWindowTitle(tr("RSS listing example"));
            resize(640, 480);
}


void RSSListing::fetch(){
    // cập nhật UI để tránh viejc người dùng ấn khi đang tải
    lineEdit->setReadOnly(true);
    fetchButton->setEnabled(false);
    treeWidget->clear();

    // khởi tạo request yeeu cầu tải
    QUrl url(lineEdit->text());
    QNetworkRequest request(url);

    currentReply = manager->get(request);

    connect(currentReply, &QNetworkReply::finished, this, &RSSListing::consumeData);
    connect(currentReply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::error),
                this, &RSSListing::error);
}

void RSSListing::error(QNetworkReply::NetworkError code){
    qWarning() << "Error retrieving RSS feed:" << code;
        xml.clear();
}

void RSSListing::consumeData(){

    // kiểm tra trạng thái của HTTP
    QVariant status = currentReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
    if(status.isValid()){
        int statusCode = status.toInt();

        if(statusCode >= 200 && statusCode < 300) parseXml();
    }

    currentReply->deleteLater();

}

void RSSListing::get(const QUrl &url){
    if(currentReply){
        currentReply->disconnect(this);
        currentReply->deleteLater();
    }


    currentReply = url.isValid() ? manager->get(QNetworkRequest(url)) : nullptr;
    if(currentReply){
        connect(currentReply, &QNetworkReply::readyRead, this, &RSSListing::consumeData);
        connect(currentReply, &QNetworkReply::finished, this, &RSSListing::finished);
     }

    xml.setDevice(currentReply);
}

void RSSListing::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);
    // Khôi phục trạng thái UI
    lineEdit->setReadOnly(false);
    fetchButton->setEnabled(true);
}


void RSSListing::parseXml()
{
    // 1. Vòng lặp đọc qua từng token của tài liệu XML
    while (!xml.atEnd()) {
        xml.readNext();

        // 2. Xử lý khi gặp thẻ mở <tag>
        if (xml.isStartElement()) {
            if (xml.name() == u"item") {
                // Lấy thuộc tính nếu có (ví dụ: rss:about)
            linkString = xml.attributes().value("rss:about").toString();
            titleString.clear();
            }
            // Lưu tên thẻ hiện tại để biết dữ liệu text bên trong thuộc về thẻ nào
            currentTag = xml.name().toString();
        }

        // 3. Xử lý khi gặp thẻ đóng </tag>
        else if (xml.isEndElement()) {
            if (xml.name() == u"item") {
                // Khi kết thúc một <item>, tạo một dòng mới trên giao diện (QTreeWidget)
                QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget);
                item->setText(0, titleString);
                item->setText(1, linkString);
            }
        }

        // 4. Xử lý nội dung văn bản bên trong thẻ
        else if (xml.isCharacters() && !xml.isWhitespace()) {
            if (currentTag == u"title")
                titleString += xml.text();
            else if (currentTag == u"link")
                linkString += xml.text();
        }
    }

    // 5. Kiểm tra lỗi sau khi kết thúc luồng dữ liệu
    if (xml.error() && xml.error() != QXmlStreamReader::PrematureEndOfDocumentError) {
        qWarning() << "XML ERROR at line" << xml.lineNumber() << ":" << xml.errorString();
    }
}
RSSListing::~RSSListing()
{
}

