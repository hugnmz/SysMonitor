#include "addstudent.h"
#include "ui_addstudent.h"
#include "addstudent.h"
#include <QString>
#include "studentrepo.h"
#include <QVBoxLayout>
#include <QHBoxLayout>


addstudent::addstudent(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addstudent)
{
    ui->setupUi(this);
    connect(ui->btnExit, &QPushButton::clicked, this, &QWidget::close);

}

void addstudent::on_btnAdd_clicked(){
    QString name = ui->inputName->text();

    StudentRepo s;
    s.addStudent(name);


    emit studentAdded();
    this->close();
}

addstudent::~addstudent()
{
    delete ui;
}
