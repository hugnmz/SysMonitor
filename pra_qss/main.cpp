#include "mainwindow.h"

#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QFile file(":/style.qss"); // Đường dẫn bắt đầu bằng dấu :/ của Resource
        if (file.open(QFile::ReadOnly)) {
            QString styleSheet = QLatin1String(file.readAll());
            a.setStyleSheet(styleSheet);
            file.close();
        }

    MainWindow w;
    w.show();
    return a.exec();
}
