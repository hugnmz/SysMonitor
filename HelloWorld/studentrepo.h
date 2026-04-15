#ifndef STUDENTREPO_H
#define STUDENTREPO_H
#include <QString>
#include <QList>
#include "Student.h"

class StudentRepo{
public:
    StudentRepo();

    void addStudent(const QString &name);
    QList<Student> getAllStudents();
    void deleteStudent(int id);

};
#endif // STUDENTREPO_H
