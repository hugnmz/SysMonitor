#include "studentlist.h"
#include "ui_studentlist.h"
#include "studentrepo.h"



studentlist::studentlist(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::studentlist)
{
    ui->setupUi(this);
}

QList<Student> studentlist::loadData(){

    QList<Student> students = StudentRepo().getAllStudents();
    return students;
}

studentlist::~studentlist()
{
    delete ui;
}
