#include "group.h"


//group::group(QObject *parent = 0) : QObject(parent)
//{

//}
group::group(){}
group::group(user * user, QString groupName, teacher * thr, int groupType)
{
    if(NULL==user || NULL == thr)
    {
        qDebug() << "NULL Pointer!";
        return;
    }
    this->groupID = user->getUserID();
    this->groupName = groupName;
    this->groupTeacherID = thr->getTeacherID();
    this->groupType = groupType;
}
group::~group()
{

}

void group::setGroupID(user * user)
{
    if(NULL==user)
    {
        qDebug() << "NULL Pointer!";
        return;
    }
    this->groupID = user->getUserID();
}
void group::setGroupName(QString groupName)
{
    this->groupName = groupName;
}
void group::setGroupTeacherID(teacher * thr)
{
    this->groupTeacherID = thr->getTeacherID();
}
void group::setGroupType(int groupType)
{
    this->groupType = groupType;
}

int group::getGroupID() const
{
    return this->groupID;
}
QString group::getGroupName() const
{
    return this->groupName;
}
int group::getGroupTeacherID() const
{
    return this->groupTeacherID;
}
int group::getGroupType() const
{
    return this->groupType;
}

QString group::getinfo() const
{
    QString info = QString ("groupID:%1 , groupName:%2 , groupTeacherID:%3 , groupType:%4")
            .arg(this->groupID)
            .arg(this->groupName)
            .arg(this->groupTeacherID)
            .arg(this->groupType);
    return info;
}

group & group::operator= (const group & another)  //重写=操作符
{
    this->groupID = another.groupID;
    this->groupName = another.groupName;
    this->groupTeacherID = another.groupTeacherID;
    this->groupType = another.groupType;

    return *this;
}
bool group::operator== (group & another) const  //重写==操作符
{
    if(this->groupID == another.groupID && this->groupName == another.groupName
            && this->groupTeacherID == another.groupTeacherID && this->groupType == another.groupType)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool group::operator!= (group & another) const  //重写!=操作符
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
