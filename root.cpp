#include "root.h"

//root::root(QObject *parent) : QObject(parent)
//{

//}

root::root(){}//无参构造函数
root::root(int rootID,
user * us,
QString rootName,
bool rootSex)//有参构造函数
{
    if(NULL == us)
    {
        qDebug()<<"NULL Pointer";
        return;
    }
    this->rootID = rootID;
    this->rootUserID = us->getUserID();
    this->rootName = rootName;
    this->rootSex = rootSex;
}
root::~root(){}

void root::setRootID(int rootID)
{
    this->rootID = rootID;
}
void root::setUserID(user * us)
{
    if(NULL == us)
    {
        qDebug()<<"NULL Pointer!";
        return;
    }
    this->rootUserID = us->getUserID();
}
void root::setRootName(QString rootName)
{
    this->rootName = rootName;
}
void root::setRootSex(bool rootSex)
{
    this->rootSex = rootSex;
}

int root::getRootID() const
{
    return this->rootID;
}
int root::getRootUserID() const
{
    return this->rootUserID;
}
QString root::getRootName() const
{
    return this->rootName;
}
bool root::getRootSex() const
{
    return this->rootSex;
}

QString root::getInfo() const
{
    QString info = QString("rootID:%1 , rootUserID:%2 , rootName:%3 , rootSex:%4")
            .arg(this->rootID)
            .arg(this->rootUserID)
            .arg(this->rootName)
            .arg(this->rootSex);
    return info;
}

root & root::operator =(root & another)  //重载=操作符
{
    this->rootID = another.rootID;
    this->rootUserID = another.rootUserID;
    this->rootName = another.rootName;
    this->rootSex = another.rootSex;
    return *this;
}
bool root::operator ==(root & another) const //重载==操作符
{
    if(this->rootID == another.rootID
            && this->rootUserID == another.rootUserID
            && this->rootName == another.rootName
            && this->rootSex == another.rootSex)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool root::operator !=(root & another) const //重载!=操作符
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
