#ifndef SIG_H
#define SIG_H

#include <QWidget>

namespace Ui {
class sig;
}

class sig : public QWidget
{
    Q_OBJECT

public:
    explicit sig(QWidget *parent = nullptr);
    ~sig();

private:
    Ui::sig *ui;
};

#endif // SIG_H
