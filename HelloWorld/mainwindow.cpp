#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <addstudent.h>
#include <studentlist.h>
#include <QList>
#include <Student.h>
#include <studentrepo.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    list = new StudentRepo();
    add = new addstudent();
    showData();

}

void MainWindow::showData(){

    ui->tblStudent->setRowCount(0);
    QList<Student> students = list->getAllStudents();
    ui->tblStudent->setColumnCount(2);
    ui->tblStudent->setHorizontalHeaderLabels({"Id", "Name"});

    for(Student s : students){
        int r = ui->tblStudent->rowCount();
        ui->tblStudent->insertRow(r);

        ui->tblStudent->setItem(r, 0,new QTableWidgetItem(QString::number(s.id)));
        ui->tblStudent->setItem(r, 1,new QTableWidgetItem(s.name));

    }
}
void MainWindow::on_btnOpen_clicked()
{
    addstudent *dlg = new addstudent(this);

    connect(dlg, &addstudent::studentAdded,
            this, &MainWindow::showData);

    dlg->show();
}
MainWindow::~MainWindow()
{
    delete ui;
    delete list;
    delete add;
}

