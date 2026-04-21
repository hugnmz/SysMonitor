#ifndef INTERNETRADIO_H
#define INTERNETRADIO_H

#include <QWidget>

namespace Ui {
class internetradio;
}

class internetradio : public QWidget
{
    Q_OBJECT

public:
    explicit internetradio(QWidget *parent = nullptr);
    ~internetradio();

private:
    Ui::internetradio *ui;
};

#endif // INTERNETRADIO_H
