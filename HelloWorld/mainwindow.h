#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <addstudent.h>
#include <studentrepo.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnOpen_clicked();

private:
    void showData();

private:
    StudentRepo *list;
    addstudent *add;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
