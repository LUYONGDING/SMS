#include "user.h"

//user::user(QObject *parent) : QObject(parent)
//{

//}

user::user(){}
user::user(int id, QString userName, QString userPasswd, int userType)
{
    this->id = id;
    this->userName = userName;
    this->userPasswd = userPasswd;
    this->userType = userType;
}
user::~user(){}

void user::setID(int id)
{
    this->id = id;
}

void user::setUserName(QString userName)
{
    this->userName = userName;
}

void user::setUserPasswd(QString userPasswd)
{
    this->userPasswd = userPasswd;
}

void user::setUserType(int userType)
{
    this->userType = userType;
}

int user::getID() const
{
    return this->id;
}
QString user::getUserName() const
{
    return this->userName;
}
QString user::getUserPasswd() const
{
    return this->userPasswd;
}
int user::getUserType() const
{
    return this->userType;
}

QString user::getinfo() const
{
    QString info = QString ("userID:%1 , userName:%2 , userPasswd:%3 , userType:%4")
                            .arg(this->id)
                            .arg(this->userName)
                            .arg(this->userPasswd)
                            .arg(this->userType);
    return info;
}

user & user::operator= (user & another) //重写=操作符
{
    this->id = another.id;
    this->userName = another.userName;
    this->userPasswd = another.userPasswd;
    this->userType = another.userType;

    return *this;
}
bool user::operator ==(user & another) const //重写==操作符
{
    if(this->id == another.id && this->userName == another.userName &&
            this->userPasswd == another.userPasswd && this->userType == another.userType)
    {
        return true;
    }
    else
    {
        return false;
    }
}
bool user::operator !=(user & another) const //重写!=操作符
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
