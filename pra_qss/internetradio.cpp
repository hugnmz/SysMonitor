#include "internetradio.h"
#include "ui_internetradio.h"

internetradio::internetradio(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::internetradio)
{
    ui->setupUi(this);
}

internetradio::~internetradio()
{
    delete ui;
}
