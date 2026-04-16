#ifndef SIGNAL_H
#define SIGNAL_H

#include <QMainWindow>

namespace Ui {
class Signal;
}

class Signal : public QMainWindow
{
    Q_OBJECT

public:
    explicit Signal(QWidget *parent = nullptr); // = nullptr vì nếu ko truyền được mặc định window đọc lập, nếu có thuộc về widget cha
    ~Signal(); // destructor(giải phóng UI, object)

private:
    Ui::Signal *ui;
}; // ui là con trỏ dữ kiện, chứa tất cả button, label, input...

#endif // SIGNAL_H
