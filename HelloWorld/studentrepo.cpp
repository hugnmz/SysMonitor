#include "studentrepo.h"
#include "addstudent.h"
#include <QtSql>
#include <QDebug>


StudentRepo::StudentRepo(){

}

void StudentRepo::addStudent(const QString &name){
    QSqlQuery query;

    query.prepare("INSERT INTO student(name) VALUES(?)");
    query.addBindValue(name);

    query.exec();

}

QList<Student> StudentRepo::getAllStudents(){

    QList<Student> students;

    QSqlQuery query("SELECT id,name FROM student");
    while(query.next()){

        Student s;
        s.id = query.value(0).toInt();
        s.name = query.value(1).toString();
        students.append(s);
    }

    return students;
}

void StudentRepo::deleteStudent(int id){
    QSqlQuery query("DELETE FROM student where id = ?");
    query.addBindValue(id);

    query.exec();
}
