#include "Signal.h"
#include "ui_Signal.h"

Signal::Signal(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::Signal)
{
    ui->setupUi(this);

    // truyền vào đối tượng exit, -> phát ra 1 tín hiệu để biết là đã click nên nút đó, slot là hàm phương thức được thực thi khi signal dc phát ra, this chính là cái object signal
    connect(ui->btnExit, SIGNAL(clicked()), this, SLOT(close()));
}
Signal::~Signal()
{
    delete ui;
}

