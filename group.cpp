#include "group.h"


//group::group(QObject *parent = 0) : QObject(parent)
//{

//}
group::group(){}
group::group(user * user, QString groupName, QString groupTeacher, int groupType)
{
    if(NULL==user)
    {
        qDebug() << "user is NULL!";
        return;
    }
    this->groupID = user->getID();
    this->groupName = groupName;
    this->groupTeacher = groupTeacher;
    this->groupType = groupType;
}
group::~group()
{

}

void group::setGroupID(user * user)
{
    this->groupID = user->getID();
}
void group::setGroupName(QString groupName)
{
    this->groupName = groupName;
}
void group::setGroupTeacher(QString groupTeacher)
{
    this->groupTeacher = groupTeacher;
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
QString group::getGroupTeacher() const
{
    return this->groupTeacher;
}
int group::getGroupType() const
{
    return this->groupType;
}

QString group::getinfo() const
{
    QString info = QString ("groupID:%1 , groupName:%2 , groupTeacher:%3 , groupType:%4")
                            .arg(this->groupID)
                            .arg(this->groupName)
                            .arg(this->groupTeacher)
                            .arg(this->groupType);
    return info;
}

group & group::operator= (group & another)  //重写=操作符
{
    this->groupID = another.groupID;
    this->groupName = another.groupName;
    this->groupTeacher = another.groupTeacher;
    this->groupType = another.groupType;

    return *this;
}
bool group::operator== (group & another) const  //重写==操作符
{
    if(this->groupID == another.groupID && this->groupName == another.groupName
            && this->groupTeacher == another.groupTeacher && this->groupType == another.groupType)
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
