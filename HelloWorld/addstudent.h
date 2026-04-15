#ifndef ADDSTUDENT_H
#define ADDSTUDENT_H

#include <QWidget>

namespace Ui {
class addstudent;
}

class addstudent : public QWidget
{
    Q_OBJECT

public:
    explicit addstudent(QWidget *parent = nullptr);
    ~addstudent();

private slots:
    void on_btnAdd_clicked();

//private slots:
//    void addSuccess();
signals:
    void studentAdded();
private:
    QWidget *widget;
    Ui::addstudent *ui;
};

#endif // ADDSTUDENT_H
