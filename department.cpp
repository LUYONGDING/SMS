#include "department.h"

//department::department(QObject *parent) : QObject(parent)
//{

//}
department::department(){}
department::department(int departmentID, const group * gp, QString departmentName, QString departmentIntroduction)
{
    if(NULL == gp)
    {
        qDebug() <<"NULL Pointer";
        return;
    }
    this->departmentID = departmentID;
    this->departmentGroupID = gp->getGroupID();
    this->departmentName = departmentName;
    this->departmentIntroduction = departmentIntroduction;
}
department::~department(){}

void department::setDepartmentID(int departmentID)
{
    this->departmentID = departmentID;
}
void department::setDepartmentGroupID(const group * gp)
{
    if(NULL == gp)
    {
        qDebug() <<"NULL Pointer";
        return;
    }
    this->departmentGroupID = gp->getGroupID();
}
void department::setDepartmentGroupID(int ID)
{
    this->departmentGroupID = ID;
}
void department::setDepartmentName(QString departmentName)
{
    this->departmentName = departmentName;
}
void department::setDepartmentIntroduction(QString departmentIntroduction)
{
    this->departmentIntroduction = departmentIntroduction;
}
int department::getDepartmentID() const
{
    return this->departmentID;
}
int department::getDepartmentGroupID() const
{
    return this->departmentGroupID;
}
QString department::getDepartmentName() const
{
    return this->departmentName;
}
QString department::getDepartmentIntroduction() const
{
    return this->departmentIntroduction;
}
QString department::getInfo() const
{
    QString info = QString("departmentID:%1 , departmentGroupID:%2 , departmentName:%3 , departmentIntroduction:%4")
            .arg(this->departmentID)
            .arg(this->departmentGroupID)
            .arg(this->departmentName)
            .arg(this->departmentIntroduction);
    return info;
}

department & department::operator =(department & another)  //重载=操作符
{
    this->departmentGroupID = another.departmentGroupID;
    this->departmentID = another.departmentID;
    this->departmentName = another.departmentName;
    this->departmentIntroduction = another.departmentIntroduction;
    return *this;
}
bool department::operator ==(department & another) const   //重载==操作符
{
    if(this->departmentGroupID==another.departmentGroupID && this->departmentID == another.departmentID
            && this->departmentName == another.departmentName && this->departmentIntroduction == another.departmentIntroduction)
    {
        return true;
    }else
    {
        return false;
    }
}
bool department::operator !=(department & another) const   //重载!=操作符
{
    if(*(this) == another)
    {
        return false;
    }else
    {
        return true;
    }
}
