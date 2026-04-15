#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include <QDialog>
#include <Student.h>

namespace Ui {
class studentlist;
}

class studentlist : public QDialog
{
    Q_OBJECT

public:
    explicit studentlist(QWidget *parent = nullptr);
    ~studentlist();

public:
    QList<Student> loadData();


private:
    Ui::studentlist *ui;
};

#endif // STUDENTLIST_H
