#ifndef STUDENTDEPENDENCE_H
#define STUDENTDEPENDENCE_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "group.h"
#include "department.h"
#include "student.h"

class studentDependence : public QObject
{
    Q_OBJECT
public:
    //explicit studentDependence(QObject *parent = 0);
    studentDependence();
    studentDependence(group * gp, department * dp, QString dependenceDuty, int dependenceID, student * stu);
    ~studentDependence();

    //设置和获得成员的接口
    void setDependenceGroupID(group * gp);
    void setDependenceDepartmentID(department * dp);
    void setDependenceDuty(QString dependenceDuty);
    void setDependenceID(int dependenceID);
    void setDependenceStudentID(student * stu);

    int getDependenceGroupID() const;
    int getDependenceDepartmentID() const;
    QString getDependenceDuty() const;
    int getDependenceID() const;
    int getDependenceStudentID() const;

    QString getInfo() const;  //获得信息

    studentDependence & operator =(const studentDependence & another);    //重载=操作符
    bool operator ==(studentDependence & another) const;    //重载==操作符
    bool operator !=(studentDependence & another) const;    //重载!=操作符

protected:
private:
    int dependenceGroupID;
    int dependenceDepartmentID;
    QString dependenceDuty;
    int dependenceID;
    int dependenceStudentID;
signals:

public slots:
};

#endif // STUDENTDEPENDENCE_H
