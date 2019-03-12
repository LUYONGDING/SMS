#include "studentdependence.h"

//studentDependence::studentDependence(QObject *parent) : QObject(parent)
//{

//}
studentDependence::studentDependence(){}
studentDependence::studentDependence(group * gp, department * dp, QString dependenceDuty, int dependenceID, student * stu)
{
    if(NULL==gp || NULL == dp || NULL == stu)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->dependenceGroupID = gp->getGroupID();
    this->dependenceDepartmentID = dp->getDepartmentID();
    this->dependenceDuty = dependenceDuty;
    this->dependenceID = dependenceID;
    this->dependenceStudentID = stu->getStudentID();
}
studentDependence::~studentDependence()
{

}
void studentDependence::setDependenceGroupID(group * gp)
{
    if(NULL == gp)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->dependenceGroupID = gp->getGroupID();
}
void studentDependence::setDependenceDepartmentID(department * dp)
{
    if(NULL == dp)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->dependenceDepartmentID = dp->getDepartmentID();
}
void studentDependence::setDependenceDuty(QString dependenceDuty)
{
    this->dependenceDuty = dependenceDuty;
}
void studentDependence::setDependenceID(int dependenceID)
{
    this->dependenceID = dependenceID;
}
void studentDependence::setDependenceStudentID(student * stu)
{
    if(NULL == stu)
    {
        qDebug()<<"NULL Pointer";
    }
    this->dependenceStudentID = stu->getStudentID();
}
int studentDependence::getDependenceGroupID() const
{
    return this->dependenceGroupID;
}
int studentDependence::getDependenceDepartmentID() const
{
    return this->dependenceDepartmentID;
}
QString studentDependence::getDependenceDuty() const
{
    return this->dependenceDuty;
}
int studentDependence::getDependenceID() const
{
    return this->dependenceID;
}
int studentDependence::getDependenceStudentID() const
{
    return this->dependenceStudentID;
}
QString studentDependence::getInfo() const
{
    QString info = QString ("dependenceGroupID:%1 , dependenceDepartmentID:%2 , dependenceDuty:%3 , dependenceID:%4 , dependenceStudentID:%5")
            .arg(this->dependenceGroupID)
            .arg(this->dependenceDepartmentID)
            .arg(this->dependenceDuty)
            .arg(this->dependenceID)
            .arg(this->dependenceStudentID);
    return info;
}
studentDependence & studentDependence::operator =(const studentDependence & another)    //重载=操作符
{
    this->dependenceGroupID = another.dependenceGroupID;
    this->dependenceDepartmentID = another.dependenceDepartmentID;
    this->dependenceDuty = another.dependenceDuty;
    this->dependenceID = another.dependenceID;
    this->dependenceStudentID = dependenceStudentID;
    return *this;
}
bool studentDependence::operator ==(studentDependence & another) const    //重载==操作符
{
    if(this->dependenceGroupID == another.dependenceGroupID &&
            this->dependenceDepartmentID == another.dependenceDepartmentID &&
            this->dependenceDuty == another.dependenceDuty &&
            this->dependenceID == another.dependenceID &&
            this->dependenceStudentID == dependenceStudentID)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool studentDependence::operator !=(studentDependence & another) const    //重载!=操作符
{
    if(*(this) == another)
    {
        return false;
    }
    else
    {
        return true;
    }
}
