#include "teacher.h"

teacher::teacher(QObject *parent) : QObject(parent)
{

}
teacher::teacher(){} //无参构造
teacher::teacher(int teacherID,
user * us,
QString teacherName,
bool teacherSex)   //有参构造
{
    if(NULL == us)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->teacherID = teacherID;
    this->teacherUserID = us->getUserID();
    this->teacherName = teacherName;
    this->teacherSex = teacherSex;
}
teacher::~teacher(){}

void teacher::setTeacherID(int teacherID)
{
    this->teacherID = teacherID;
}
void teacher::setTeahcerUserID(user * us)
{
    if(NULL == us)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->teacherUserID = us->getUserID();
}
void  teacher::setTeahcerUserID(int ID)
{
    this->teacherID = ID;
}
void teacher::setTeacherName(QString teacherName)
{
    this->teacherName = teacherName;
}
void teacher::setTeacherSex(bool teacherSex)
{
    this->teacherSex = teacherSex;
}
int teacher::getTeacherID() const
{
    return this->teacherID;
}
int teacher::getTeacherUserID() const
{
    return this->teacherUserID;
}
QString teacher::getTeacherName() const
{
    return this->teacherName;
}
bool teacher::getTeacherSex() const
{
    return this->teacherSex;
}
QString teacher::getInfo() const
{
    QString info = QString ("teacherID:%1 , teacherUserID:%2 , teacherName:%3 , teacherSex:%4")
            .arg(this->teacherID)
            .arg(this->teacherUserID)
            .arg(this->teacherName)
            .arg(this->teacherSex);
    return info;
}
teacher & teacher::operator =(teacher & another)    //重载=操作符
{
    this->teacherID = another.teacherID;
    this->teacherUserID = another.teacherUserID;
    this->teacherName = another.teacherName;
    this->teacherSex = another.teacherSex;
    return *this;
}
bool teacher::operator ==(teacher & another) const   //重载==操作符
{
    if(this->teacherID == another.teacherID
            && this->teacherUserID == another.teacherUserID
            && this->teacherName == another.teacherName
            && this->teacherSex == another.teacherSex)
    {
        return true;
    }else
    {
        return false;
    }
}
bool teacher::operator !=(teacher & another) const   //重载!=操作符
{
    if(*(this) == another)
    {
        return true;
    }
    else
    {
        return false;
    }
}
