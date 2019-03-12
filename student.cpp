#include "student.h"

//student::student(QObject *parent) : QObject(parent)
//{

//}
student::student()
{

}
student::~student()
{

}
student::student(int studentID, bool studentSex, QString studentName)
{
    this->studentID = studentID;
    this->studentSex = studentSex;
    this->studentName = studentName;
}

void student::setStudentID(int studentID)
{
    this->studentID = studentID;
}
void student::setStudentSex(bool studentSex)
{
    this->studentSex = studentSex;
}
void student::setStudentName(QString studentName)
{
    this->studentName = studentName;
}

int student::getStudentID() const
{
    return this->studentID;
}
bool student::getStudentSex() const
{
    return this->studentSex;
}
QString student::getStudentName() const
{
    return this->studentName;
}

//获得信息
QString student::getinfo() const
{
    QString info = QString ("studentID:%1 , studentSex:%2 , studentName:%3")
            .arg(this->studentID)
            .arg(this->studentSex)
            .arg(this->studentName);
    return info;
}

student & student::operator =(student & another)   //重载=操作符
{
    this->studentID = another.studentID;
    this->studentSex = another.studentSex;
    this->studentName = another.studentName;
    return *this;
}
bool student::operator ==(student & another) const    //重载==操作符
{
    if(this->studentID == another.studentID && this->studentName == another.studentName
            && this->studentSex == studentSex)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool student::operator !=(student & another) const    //重载!=操作符
{
    if((*this) == another)
    {
        return false;
    }
    else
    {
        return true;
    }
}
