#include "sig.h"
#include "ui_sig.h"

sig::sig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::sig)
{
    ui->setupUi(this);

    connect(ui->btnExit, &QPushButton::clicked, this, SLOT(close()));
}

sig::~sig()
{
    delete ui;
}
