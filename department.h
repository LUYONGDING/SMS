#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <QObject>
#include <QString>
#include <QDebug>
#include "group.h"

class department : public QObject
{
    Q_OBJECT
public:
    //explicit department(QObject *parent = 0);
    department();
    department(int departmentID, const group * gp, QString departmentName, QString departmentIntroduction);
    ~department();

    //设置和获得成员属性的接口
    void setDepartmentID(int departmentID);
    void setDepartmentGroupID(const group * gp);
    void setDepartmentGroupID(int ID);
    void setDepartmentName(QString departmentName);
    void setDepartmentIntroduction(QString departmentIntroduction);

    int getDepartmentID() const;
    int getDepartmentGroupID() const;
    QString getDepartmentName() const;
    QString getDepartmentIntroduction() const;

    QString getInfo() const;    //获得信息

    department & operator =(department & another);  //重载=操作符
    bool operator ==(department & another) const;   //重载==操作符
    bool operator !=(department & another) const;   //重载!=操作符


protected:
private:
    int departmentID;   //部门编号
    int departmentGroupID;  //部门所属社团编号,关联group中的groupID
    QString departmentName; //部门名字
    QString departmentIntroduction; //部门简述
signals:

public slots:
};

#endif // DEPARTMENT_H
