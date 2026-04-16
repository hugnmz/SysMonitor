#include "rsslisting.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    RSSListing w(QStringLiteral("https://www.qt.io/blog/rss.xml"));
    w.show();
    return a.exec();
}
