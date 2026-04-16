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

RSSListing::~RSSListing()
{
}

